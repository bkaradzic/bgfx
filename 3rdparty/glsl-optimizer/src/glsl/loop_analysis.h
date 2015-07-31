/* -*- c++ -*- */
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

#pragma once
#ifndef LOOP_ANALYSIS_H
#define LOOP_ANALYSIS_H

#include "ir.h"
#include "glsl_types.h"
#include "program/hash_table.h"

/**
 * Analyze and classify all variables used in all loops in the instruction list
 */
extern class loop_state *
analyze_loop_variables(exec_list *instructions);


/**
 * Fill in loop control fields
 *
 * Based on analysis of loop variables, this function tries to remove
 * redundant sequences in the loop of the form
 *
 *  (if (expression bool ...) (break))
 *
 * For example, if it is provable that one loop exit condition will
 * always be satisfied before another, the unnecessary exit condition will be
 * removed.
 */
extern bool
set_loop_controls(exec_list *instructions, loop_state *ls);


extern bool
unroll_loops(exec_list *instructions, loop_state *ls,
             const struct gl_shader_compiler_options *options);

ir_rvalue *
find_initial_value(ir_loop *loop, ir_variable *var, ir_instruction **out_containing_ir);

int
calculate_iterations(ir_rvalue *from, ir_rvalue *to, ir_rvalue *increment,
		     enum ir_expression_operation op);


/**
 * Tracking for all variables used in a loop
 */
class loop_variable_state : public exec_node {
public:
   class loop_variable *get(const ir_variable *);
   class loop_variable *insert(ir_variable *);
   class loop_variable *get_or_insert(ir_variable *, bool in_assignee);
   class loop_terminator *insert(ir_if *);


   /**
    * Variables that have not yet been classified
    */
   exec_list variables;

   /**
    * Variables whose values are constant within the body of the loop
    *
    * This list contains \c loop_variable objects.
    */
   exec_list constants;

   /**
    * Induction variables for this loop
    *
    * This list contains \c loop_variable objects.
    */
   exec_list induction_variables;
   int private_induction_variable_count;

   /**
    * Simple if-statements that lead to the termination of the loop
    *
    * This list contains \c loop_terminator objects.
    *
    * \sa is_loop_terminator
    */
   exec_list terminators;

   /**
    * If any of the terminators in \c terminators leads to termination of the
    * loop after a constant number of iterations, this is the terminator that
    * leads to termination after the smallest number of iterations.  Otherwise
    * NULL.
    */
   loop_terminator *limiting_terminator;

   /**
    * Hash table containing all variables accessed in this loop
    */
   hash_table *var_hash;

   /**
    * Number of ir_loop_jump instructions that operate on this loop
    */
   unsigned num_loop_jumps;

   /**
    * Whether this loop contains any function calls.
    */
   bool contains_calls;

   loop_variable_state()
   {
      this->num_loop_jumps = 0;
      this->contains_calls = false;
      this->var_hash = hash_table_ctor(0, hash_table_pointer_hash,
				       hash_table_pointer_compare);
      this->limiting_terminator = NULL;
   }

   ~loop_variable_state()
   {
      hash_table_dtor(this->var_hash);
   }

   DECLARE_RALLOC_CXX_OPERATORS(loop_variable_state)
};


class loop_variable : public exec_node {
public:
   /** The variable in question. */
   ir_variable *var;

   /** Is the variable read in the loop before it is written? */
   bool read_before_write;

   /** Are all variables in the RHS of the assignment loop constants? */
   bool rhs_clean;

   /**
    * Is there an assignment to the variable that is conditional, or inside a
    * nested loop?
    */
   bool conditional_or_nested_assignment;

   /** Reference to the first assignment to the variable in the loop body. */
   ir_assignment *first_assignment;

   /** Reference to initial value outside of the loop. */
   ir_rvalue *initial_value;
   /** IR that assigned the initial value. */
   ir_instruction *initial_value_ir;

   /** Number of assignments to the variable in the loop body. */
   unsigned num_assignments;

   /**
    * Increment value for a loop induction variable
    *
    * If this is a loop induction variable, the amount by which the variable
    * is incremented on each iteration through the loop.
    *
    * If this is not a loop induction variable, NULL.
    */
   ir_rvalue *increment;


   inline bool is_induction_var() const
   {
      /* Induction variables always have a non-null increment, and vice
       * versa.
       */
      return this->increment != NULL;
   }


   inline bool is_loop_constant() const
   {
      const bool is_const = (this->num_assignments == 0)
         || (((this->num_assignments == 1)
	     && !this->conditional_or_nested_assignment
	     && !this->read_before_write
             && this->rhs_clean) || this->var->data.read_only);

      /* If the RHS of *the* assignment is clean, then there must be exactly
       * one assignment of the variable.
       */
      assert((this->rhs_clean && (this->num_assignments == 1))
	     || !this->rhs_clean);

      return is_const;
   }

   void record_reference(bool in_assignee,
                         bool in_conditional_code_or_nested_loop,
                         ir_assignment *current_assignment);
};


class loop_terminator : public exec_node {
public:
   loop_terminator()
      : ir(NULL), iterations(-1)
   {
   }

   /**
    * Statement which terminates the loop.
    */
   ir_if *ir;

   /**
    * The number of iterations after which the terminator is known to
    * terminate the loop (if that is a fixed value).  Otherwise -1.
    */
   int iterations;
};


class loop_state {
public:
   ~loop_state();

   /**
    * Get the loop variable state data for a particular loop
    */
   loop_variable_state *get(const ir_loop *);

   loop_variable_state *insert(ir_loop *ir);
	
   loop_variable_state* get_for_inductor (const ir_variable*);
   bool insert_inductor(loop_variable* loopvar, loop_variable_state* state, ir_loop* loop);
   void insert_non_inductor(ir_variable *var);

   bool loop_found;

private:
   loop_state();

   /**
    * Hash table containing all loops that have been analyzed.
    */
   hash_table *ht;
	
   /**
    * Hash table from ir_variables to loop state, for induction variables.
    */
   hash_table *ht_inductors;
   hash_table *ht_non_inductors;
 

   void *mem_ctx;

   friend loop_state *analyze_loop_variables(exec_list *instructions);
};

#endif /* LOOP_ANALYSIS_H */
