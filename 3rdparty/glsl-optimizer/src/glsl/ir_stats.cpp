#include "ir.h"
#include "ir_visitor.h"
#include "ir_unused_structs.h"
#include "glsl_types.h"

struct ir_stats_counter_visitor : public ir_hierarchical_visitor {
	ir_stats_counter_visitor()
		: math(0), tex(0), flow(0)
	{
	}

	virtual ir_visitor_status visit_leave(class ir_loop *)
	{
		++flow;
		return visit_continue;
	}
	virtual ir_visitor_status visit_leave(class ir_expression *)
	{
		++math;
		return visit_continue;
	}
	virtual ir_visitor_status visit_leave(class ir_texture *)
	{
		++tex;
		return visit_continue;
	}
	virtual ir_visitor_status visit_leave(ir_assignment *ir)
	{
		if (ir && ir->rhs)
		{
			if (ir->rhs->as_constant())
				++math;
		}
		return visit_continue;
	}
	virtual ir_visitor_status visit_leave(class ir_return *)
	{
		++flow;
		return visit_continue;
	}
	virtual ir_visitor_status visit_leave(class ir_discard *)
	{
		++tex;
		return visit_continue;
	}
	virtual ir_visitor_status visit_leave(class ir_if *)
	{
		++flow;
		return visit_continue;
	}

	int math;
	int tex;
	int flow;
};

void calculate_shader_stats(exec_list* instructions, int* outMath, int* outTex, int* outFlow)
{
	ir_stats_counter_visitor v;
	v.run (instructions);
	*outMath = v.math;
	*outTex = v.tex;
	*outFlow = v.flow;
}
