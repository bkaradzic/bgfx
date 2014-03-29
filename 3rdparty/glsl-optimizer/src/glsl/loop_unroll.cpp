/*
 * Copyright © 2010 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "glsl_types.h"
#include "loop_analysis.h"
#include "ir_hierarchical_visitor.h"

namespace {

class loop_unroll_visitor : public ir_hierarchical_visitor {
public:
   loop_unroll_visitor(loop_state *state, unsigned max_iterations)
   {
      this->state = state;
      this->progress = false;
      this->max_iterations = max_iterations;
   }

   virtual ir_visitor_status visit_leave(ir_loop *ir);
   void simple_unroll(ir_loop *ir, int iterations);
   void complex_unroll(ir_loop *ir, int iterations,
                       bool continue_from_then_branch);
   void splice_post_if_instructions(ir_if *ir_if, exec_list *splice_dest);

   loop_state *state;

   bool progress;
   unsigned max_iterations;
};

} /* anonymous namespace */

static bool
is_break(ir_instruction *ir)
{
   return ir != NULL && ir->ir_type == ir_type_loop_jump
		     && ((ir_loop_jump *) ir)->is_break();
}

class loop_unroll_count : public ir_hierarchical_visitor {
public:
   int nodes;
   bool fail;

   loop_unroll_count(exec_list *list)
   {
      nodes = 0;
      fail = false;

      run(list);
   }

   virtual ir_visitor_status visit_enter(ir_assignment *ir)
   {
      nodes++;
      return visit_continue;
   }

   virtual ir_visitor_status visit_enter(ir_expression *ir)
   {
      nodes++;
      return visit_continue;
   }

   virtual ir_visitor_status visit_enter(ir_loop *ir)
   {
      fail = true;
      return visit_continue;
   }
};


/**
 * Unroll a loop which does not contain any jumps.  For example, if the input
 * is:
 *
 *     (loop (...) ...instrs...)
 *
 * And the iteration count is 3, the output will be:
 *
 *     ...instrs... ...instrs... ...instrs...
 */
void
loop_unroll_visitor::simple_unroll(ir_loop *ir, int iterations)
{
   void *const mem_ctx = ralloc_parent(ir);

   for (int i = 0; i < iterations; i++) {
      exec_list copy_list;

      copy_list.make_empty();
      clone_ir_list(mem_ctx, &copy_list, &ir->body_instructions);

      ir->insert_before(&copy_list);
   }

   /* The loop has been replaced by the unrolled copies.  Remove the original
    * loop from the IR sequence.
    */
   ir->remove();

   this->progress = true;
}


/**
 * Unroll a loop whose last statement is an ir_if.  If \c
 * continue_from_then_branch is true, the loop is repeated only when the
 * "then" branch of the if is taken; otherwise it is repeated only when the
 * "else" branch of the if is taken.
 *
 * For example, if the input is:
 *
 *     (loop (...)
 *      ...body...
 *      (if (cond)
 *          (...then_instrs...)
 *        (...else_instrs...)))
 *
 * And the iteration count is 3, and \c continue_from_then_branch is true,
 * then the output will be:
 *
 *     ...body...
 *     (if (cond)
 *         (...then_instrs...
 *          ...body...
 *          (if (cond)
 *              (...then_instrs...
 *               ...body...
 *               (if (cond)
 *                   (...then_instrs...)
 *                 (...else_instrs...)))
 *            (...else_instrs...)))
 *       (...else_instrs))
 */
void
loop_unroll_visitor::complex_unroll(ir_loop *ir, int iterations,
                                    bool continue_from_then_branch)
{
   void *const mem_ctx = ralloc_parent(ir);
   ir_instruction *ir_to_replace = ir;

   for (int i = 0; i < iterations; i++) {
      exec_list copy_list;

      copy_list.make_empty();
      clone_ir_list(mem_ctx, &copy_list, &ir->body_instructions);

      ir_if *ir_if = ((ir_instruction *) copy_list.get_tail())->as_if();
      assert(ir_if != NULL);

      ir_to_replace->insert_before(&copy_list);
      ir_to_replace->remove();

      /* placeholder that will be removed in the next iteration */
      ir_to_replace =
         new(mem_ctx) ir_loop_jump(ir_loop_jump::jump_continue);

      exec_list *const list = (continue_from_then_branch)
         ? &ir_if->then_instructions : &ir_if->else_instructions;

      list->push_tail(ir_to_replace);
   }

   ir_to_replace->remove();

   this->progress = true;
}


/**
 * Move all of the instructions which follow \c ir_if to the end of
 * \c splice_dest.
 *
 * For example, in the code snippet:
 *
 *     (if (cond)
 *         (...then_instructions...
 *          break)
 *       (...else_instructions...))
 *     ...post_if_instructions...
 *
 * If \c ir_if points to the "if" instruction, and \c splice_dest points to
 * (...else_instructions...), the code snippet is transformed into:
 *
 *     (if (cond)
 *         (...then_instructions...
 *          break)
 *       (...else_instructions...
 *        ...post_if_instructions...))
 */
void
loop_unroll_visitor::splice_post_if_instructions(ir_if *ir_if,
                                                 exec_list *splice_dest)
{
   while (!ir_if->get_next()->is_tail_sentinel()) {
      ir_instruction *move_ir = (ir_instruction *) ir_if->get_next();

      move_ir->remove();
      splice_dest->push_tail(move_ir);
   }
}


ir_visitor_status
loop_unroll_visitor::visit_leave(ir_loop *ir)
{
   loop_variable_state *const ls = this->state->get(ir);
   int iterations;

   /* If we've entered a loop that hasn't been analyzed, something really,
    * really bad has happened.
    */
   if (ls == NULL) {
      assert(ls != NULL);
      return visit_continue;
   }

   /* Don't try to unroll loops where the number of iterations is not known
    * at compile-time.
    */
   if (ls->limiting_terminator == NULL)
      return visit_continue;

   iterations = ls->limiting_terminator->iterations;

   /* Don't try to unroll loops that have zillions of iterations either.
    */
   if (iterations > (int) max_iterations)
      return visit_continue;

   /* Don't try to unroll nested loops and loops with a huge body.
    */
   loop_unroll_count count(&ir->body_instructions);

   if (count.fail || count.nodes * iterations > (int)max_iterations * 25)
      return visit_continue;

   /* Note: the limiting terminator contributes 1 to ls->num_loop_jumps.
    * We'll be removing the limiting terminator before we unroll.
    */
   assert(ls->num_loop_jumps > 0);
   unsigned predicted_num_loop_jumps = ls->num_loop_jumps - 1;

   if (predicted_num_loop_jumps > 1)
      return visit_continue;

   if (predicted_num_loop_jumps == 0) {
      ls->limiting_terminator->ir->remove();
      simple_unroll(ir, iterations);
      return visit_continue;
   }

   ir_instruction *last_ir = (ir_instruction *) ir->body_instructions.get_tail();
   assert(last_ir != NULL);

   if (is_break(last_ir)) {
      /* If the only loop-jump is a break at the end of the loop, the loop
       * will execute exactly once.  Remove the break and use the simple
       * unroller with an iteration count of 1.
       */
      last_ir->remove();

      ls->limiting_terminator->ir->remove();
      simple_unroll(ir, 1);
      return visit_continue;
   }

   foreach_list(node, &ir->body_instructions) {
      /* recognize loops in the form produced by ir_lower_jumps */
      ir_instruction *cur_ir = (ir_instruction *) node;

      /* Skip the limiting terminator, since it will go away when we
       * unroll.
       */
      if (cur_ir == ls->limiting_terminator->ir)
         continue;

      ir_if *ir_if = cur_ir->as_if();
      if (ir_if != NULL) {
         /* Determine which if-statement branch, if any, ends with a
          * break.  The branch that did *not* have the break will get a
          * temporary continue inserted in each iteration of the loop
          * unroll.
          *
          * Note that since ls->num_loop_jumps is <= 1, it is impossible
          * for both branches to end with a break.
          */
         ir_instruction *ir_if_last =
            (ir_instruction *) ir_if->then_instructions.get_tail();

         if (is_break(ir_if_last)) {
            ls->limiting_terminator->ir->remove();
            splice_post_if_instructions(ir_if, &ir_if->else_instructions);
            ir_if_last->remove();
            complex_unroll(ir, iterations, false);
            return visit_continue;
         } else {
            ir_if_last =
               (ir_instruction *) ir_if->else_instructions.get_tail();

            if (is_break(ir_if_last)) {
               ls->limiting_terminator->ir->remove();
               splice_post_if_instructions(ir_if, &ir_if->then_instructions);
               ir_if_last->remove();
               complex_unroll(ir, iterations, true);
               return visit_continue;
            }
         }
      }
   }

   /* Did not find the break statement.  It must be in a complex if-nesting,
    * so don't try to unroll.
    */
   return visit_continue;
}


bool
unroll_loops(exec_list *instructions, loop_state *ls, unsigned max_iterations)
{
   loop_unroll_visitor v(ls, max_iterations);

   v.run(instructions);

   return v.progress;
}
