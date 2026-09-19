// Copyright 2011-2026 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE


//
// AUTO GENERATED! DO NOT EDIT!
//

package io.github.bkaradzic.bgfx;

import java.lang.AutoCloseable;
import java.lang.foreign.Arena;
import java.lang.foreign.FunctionDescriptor;
import java.lang.foreign.MemoryLayout;
import java.lang.foreign.MemorySegment;
import java.lang.foreign.SegmentAllocator;
import java.lang.foreign.StructLayout;
import java.lang.foreign.ValueLayout;
import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodType;
import java.lang.invoke.VarHandle;
import java.nio.file.Path;
import java.util.Objects;

import org.jspecify.annotations.NullMarked;
import org.jspecify.annotations.NullUnmarked;
import org.jspecify.annotations.Nullable;

import io.github.bkaradzic.bgfx.*;
import io.github.bkaradzic.bgfx.util.*;
import static io.github.bkaradzic.bgfx.Bgfx.*;
import static io.github.bkaradzic.bgfx.util.FFMUtil.*;

/**
 * Encoders are used for submitting draw calls from multiple threads. Only one encoder
 * per thread should be used. Use {@code begin()} to obtain an encoder for a thread.
 */
@NullMarked
public final class Encoder extends NativeObject {
	/**
	 * Wraps an opaque native pointer.
	 * @param segment native memory segment
	 */
	public Encoder(MemorySegment segment) {
		super(segment);
	}

	/**
	 * Sets a debug marker. This allows you to group graphics calls together for easy browsing in
	 * graphics debugging tools.
	 * @param _name Marker name.
	 * @param _len Marker name length (if length is INT32_MAX, it's expected that _name is zero terminated string.
	 */
	public final void setMarker(String _name, int _len) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_MARKER.invokeExact(segment(), cString(arena, _name), _len);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set render states for draw primitive.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   1. To set up more complex states use:
	 *      {@code BGFX_STATE_ALPHA_REF(_ref)},
	 *      {@code BGFX_STATE_POINT_SIZE(_size)},
	 *      {@code BGFX_STATE_BLEND_FUNC(_src, _dst)},
	 *      {@code BGFX_STATE_BLEND_FUNC_SEPARATE(_srcRGB, _dstRGB, _srcA, _dstA)},
	 *      {@code BGFX_STATE_BLEND_EQUATION(_equation)},
	 *      {@code BGFX_STATE_BLEND_EQUATION_SEPARATE(_equationRGB, _equationA)}
	 *   2. {@code BGFX_STATE_BLEND_EQUATION_ADD} is set when no other blend
	 *      equation is specified.
	 * @param _state State flags. Default state for primitive type is   triangles. See: {@code BGFX_STATE_DEFAULT}.   - {@code BGFX_STATE_DEPTH_TEST_*} - Depth test function.   - {@code BGFX_STATE_BLEND_*} - See remark 1 about BGFX_STATE_BLEND_FUNC.   - {@code BGFX_STATE_BLEND_EQUATION_*} - See remark 2.   - {@code BGFX_STATE_CULL_*} - Backface culling mode.   - {@code BGFX_STATE_WRITE_*} - Enable R, G, B, A or Z write.   - {@code BGFX_STATE_MSAA} - Enable hardware multisample antialiasing.   - {@code BGFX_STATE_PT_[TRISTRIP/LINES/POINTS]} - Primitive type.
	 * @param _rgba Sets blend factor used by {@code BGFX_STATE_BLEND_FACTOR} and   {@code BGFX_STATE_BLEND_INV_FACTOR} blend modes.
	 */
	public final void setState(@Unsigned long _state, @Unsigned int _rgba) {
		try {
			MH_ENCODER_SET_STATE.invokeExact(segment(), _state, _rgba);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set condition for rendering.
	 * @param _handle Occlusion query handle.
	 * @param _visible Render if occlusion query is visible.
	 */
	public final void setCondition(OcclusionQueryHandle _handle, boolean _visible) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_CONDITION.invokeExact(segment(), _handle.allocate(arena), _visible);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set stencil test state.
	 * @param _fstencil Front stencil state.
	 * @param _bstencil Back stencil state. If back is set to {@code BGFX_STENCIL_NONE} _fstencil is applied to both front and back facing primitives.
	 */
	public final void setStencil(@Unsigned int _fstencil, @Unsigned int _bstencil) {
		try {
			MH_ENCODER_SET_STENCIL.invokeExact(segment(), _fstencil, _bstencil);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set scissor for draw primitive.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   To scissor for all primitives in view see {@code setViewScissor}.
	 * @param _x Position x from the left corner of the window.
	 * @param _y Position y from the top corner of the window.
	 * @param _width Width of view scissor region.
	 * @param _height Height of view scissor region.
	 * @return Scissor cache index.
	 */
	public final @Unsigned short setScissor(@Unsigned short _x, @Unsigned short _y, @Unsigned short _width, @Unsigned short _height) {
		try {
			return (@Unsigned short) MH_ENCODER_SET_SCISSOR.invokeExact(segment(), _x, _y, _width, _height);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set scissor from cache for draw primitive.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   To scissor for all primitives in view see {@code setViewScissor}.
	 * @param _cache Index in scissor cache.
	 */
	public final void setScissorCached(@Unsigned short _cache) {
		try {
			MH_ENCODER_SET_SCISSOR_CACHED.invokeExact(segment(), _cache);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set model matrix for draw primitive. If it is not called,
	 * the model will be rendered with an identity model matrix.
	 * @param _mtx Pointer to first matrix in array.
	 * @param _num Number of matrices in array.
	 * @return Index into matrix cache in case the same model matrix has to be used for other draw primitive call.
	 */
	public final @Unsigned int setTransform(MemorySegment _mtx, @Unsigned short _num) {
		try {
			return (@Unsigned int) MH_ENCODER_SET_TRANSFORM.invokeExact(segment(), address(_mtx), _num);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 *  Set model matrix from matrix cache for draw primitive.
	 * @param _cache Index in matrix cache.
	 * @param _num Number of matrices from cache.
	 */
	public final void setTransformCached(@Unsigned int _cache, @Unsigned short _num) {
		try {
			MH_ENCODER_SET_TRANSFORM_CACHED.invokeExact(segment(), _cache, _num);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Reserve matrices in internal matrix cache.
	 * <p>
	 * <strong>Attention:</strong> Pointer returned can be modified until {@code frame} is called.
	 * @param _transform Pointer to {@code Transform} structure.
	 * @param _num Number of matrices.
	 * @return Index in matrix cache.
	 */
	public final @Unsigned int allocTransform(Transform _transform, @Unsigned short _num) {
		try {
			return (@Unsigned int) MH_ENCODER_ALLOC_TRANSFORM.invokeExact(segment(), address(_transform), _num);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set shader uniform parameter for draw primitive.
	 * @param _handle Uniform.
	 * @param _value Pointer to uniform data.
	 * @param _num Number of elements. Passing {@code UINT16_MAX} will use the _num passed on uniform creation.
	 */
	public final void setUniform(UniformHandle _handle, MemorySegment _value, @Unsigned short _num) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_UNIFORM.invokeExact(segment(), _handle.allocate(arena), address(_value), _num);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set index buffer for draw primitive.
	 * @param _handle Index buffer.
	 * @param _firstIndex First index to render.
	 * @param _numIndices Number of indices to render.
	 */
	public final void setIndexBuffer(IndexBufferHandle _handle, @Unsigned int _firstIndex, @Unsigned int _numIndices) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_INDEX_BUFFER.invokeExact(segment(), _handle.allocate(arena), _firstIndex, _numIndices);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set index buffer for draw primitive.
	 * @param _handle Dynamic index buffer.
	 * @param _firstIndex First index to render.
	 * @param _numIndices Number of indices to render.
	 */
	public final void setDynamicIndexBuffer(DynamicIndexBufferHandle _handle, @Unsigned int _firstIndex, @Unsigned int _numIndices) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_DYNAMIC_INDEX_BUFFER.invokeExact(segment(), _handle.allocate(arena), _firstIndex, _numIndices);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set index buffer for draw primitive.
	 * @param _tib Transient index buffer.
	 * @param _firstIndex First index to render.
	 * @param _numIndices Number of indices to render.
	 */
	public final void setTransientIndexBuffer(TransientIndexBuffer _tib, @Unsigned int _firstIndex, @Unsigned int _numIndices) {
		try {
			MH_ENCODER_SET_TRANSIENT_INDEX_BUFFER.invokeExact(segment(), address(_tib), _firstIndex, _numIndices);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set vertex buffer for draw primitive.
	 * @param _stream Vertex stream.
	 * @param _handle Vertex buffer.
	 * @param _startVertex First vertex to render.
	 * @param _numVertices Number of vertices to render.
	 */
	public final void setVertexBuffer(@Unsigned byte _stream, VertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _numVertices) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_VERTEX_BUFFER.invokeExact(segment(), _stream, _handle.allocate(arena), _startVertex, _numVertices);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set vertex buffer for draw primitive.
	 * @param _stream Vertex stream.
	 * @param _handle Vertex buffer.
	 * @param _startVertex First vertex to render.
	 * @param _numVertices Number of vertices to render.
	 * @param _layoutHandle Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.
	 */
	public final void setVertexBufferWithLayout(@Unsigned byte _stream, VertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _numVertices, VertexLayoutHandle _layoutHandle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_VERTEX_BUFFER_WITH_LAYOUT.invokeExact(segment(), _stream, _handle.allocate(arena), _startVertex, _numVertices, _layoutHandle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set vertex buffer for draw primitive.
	 * @param _stream Vertex stream.
	 * @param _handle Dynamic vertex buffer.
	 * @param _startVertex First vertex to render.
	 * @param _numVertices Number of vertices to render.
	 */
	public final void setDynamicVertexBuffer(@Unsigned byte _stream, DynamicVertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _numVertices) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_DYNAMIC_VERTEX_BUFFER.invokeExact(segment(), _stream, _handle.allocate(arena), _startVertex, _numVertices);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set vertex buffer for draw primitive.
	 * @param _stream Vertex stream.
	 * @param _handle Dynamic vertex buffer.
	 * @param _startVertex First vertex to render.
	 * @param _numVertices Number of vertices to render.
	 * @param _layoutHandle Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.
	 */
	public final void setDynamicVertexBufferWithLayout(@Unsigned byte _stream, DynamicVertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _numVertices, VertexLayoutHandle _layoutHandle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_DYNAMIC_VERTEX_BUFFER_WITH_LAYOUT.invokeExact(segment(), _stream, _handle.allocate(arena), _startVertex, _numVertices, _layoutHandle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set vertex buffer for draw primitive.
	 * @param _stream Vertex stream.
	 * @param _tvb Transient vertex buffer.
	 * @param _startVertex First vertex to render.
	 * @param _numVertices Number of vertices to render.
	 */
	public final void setTransientVertexBuffer(@Unsigned byte _stream, TransientVertexBuffer _tvb, @Unsigned int _startVertex, @Unsigned int _numVertices) {
		try {
			MH_ENCODER_SET_TRANSIENT_VERTEX_BUFFER.invokeExact(segment(), _stream, address(_tvb), _startVertex, _numVertices);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set vertex buffer for draw primitive.
	 * @param _stream Vertex stream.
	 * @param _tvb Transient vertex buffer.
	 * @param _startVertex First vertex to render.
	 * @param _numVertices Number of vertices to render.
	 * @param _layoutHandle Vertex layout for aliasing vertex buffer. If invalid handle is used, vertex layout used for creation of vertex buffer will be used.
	 */
	public final void setTransientVertexBufferWithLayout(@Unsigned byte _stream, TransientVertexBuffer _tvb, @Unsigned int _startVertex, @Unsigned int _numVertices, VertexLayoutHandle _layoutHandle) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_TRANSIENT_VERTEX_BUFFER_WITH_LAYOUT.invokeExact(segment(), _stream, address(_tvb), _startVertex, _numVertices, _layoutHandle.allocate(arena));
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set number of vertices for auto generated vertices use in conjunction
	 * with gl_VertexID.
	 * @param _numVertices Number of vertices.
	 */
	public final void setVertexCount(@Unsigned int _numVertices) {
		try {
			MH_ENCODER_SET_VERTEX_COUNT.invokeExact(segment(), _numVertices);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set instance data buffer for draw primitive.
	 * @param _idb Transient instance data buffer.
	 * @param _start First instance data.
	 * @param _num Number of data instances.
	 */
	public final void setInstanceDataBuffer(InstanceDataBuffer _idb, @Unsigned int _start, @Unsigned int _num) {
		try {
			MH_ENCODER_SET_INSTANCE_DATA_BUFFER.invokeExact(segment(), address(_idb), _start, _num);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set instance data buffer for draw primitive.
	 * @param _handle Vertex buffer.
	 * @param _startVertex First instance data.
	 * @param _num Number of data instances.
	 */
	public final void setInstanceDataFromVertexBuffer(VertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _num) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_INSTANCE_DATA_FROM_VERTEX_BUFFER.invokeExact(segment(), _handle.allocate(arena), _startVertex, _num);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set instance data buffer for draw primitive.
	 * @param _handle Dynamic vertex buffer.
	 * @param _startVertex First instance data.
	 * @param _num Number of data instances.
	 */
	public final void setInstanceDataFromDynamicVertexBuffer(DynamicVertexBufferHandle _handle, @Unsigned int _startVertex, @Unsigned int _num) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_INSTANCE_DATA_FROM_DYNAMIC_VERTEX_BUFFER.invokeExact(segment(), _handle.allocate(arena), _startVertex, _num);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set number of instances for auto generated instances use in conjunction
	 * with gl_InstanceID.
	 * @param _numInstances Number of instances.
	 */
	public final void setInstanceCount(@Unsigned int _numInstances) {
		try {
			MH_ENCODER_SET_INSTANCE_COUNT.invokeExact(segment(), _numInstances);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set texture stage for draw primitive.
	 * @param _stage Texture unit.
	 * @param _sampler Program sampler.
	 * @param _handle Texture handle.
	 * @param _flags Texture sampling mode. Default value UINT32_MAX uses   texture sampling settings from the texture.   - {@code BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]} - Mirror or clamp to edge wrap     mode.   - {@code BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]} - Point or anisotropic     sampling.
	 */
	public final void setTexture(@Unsigned byte _stage, UniformHandle _sampler, TextureHandle _handle, @Unsigned int _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_TEXTURE.invokeExact(segment(), _stage, _sampler.allocate(arena), _handle.allocate(arena), _flags);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set texture stage for draw primitive, selecting a sub-range of the
	 * texture's array layers and mip levels.
	 * @param _stage Texture unit.
	 * @param _sampler Program sampler.
	 * @param _handle Texture handle.
	 * @param _firstLayer First array layer.
	 * @param _numLayers Number of array layers.
	 * @param _firstMip First (most detailed) mip level.
	 * @param _numMips Number of mip levels.
	 * @param _flags Texture sampling mode. Default value UINT32_MAX uses   texture sampling settings from the texture.   - {@code BGFX_SAMPLER_[U/V/W]_[MIRROR/CLAMP]} - Mirror or clamp to edge wrap     mode.   - {@code BGFX_SAMPLER_[MIN/MAG/MIP]_[POINT/ANISOTROPIC]} - Point or anisotropic     sampling.
	 */
	public final void setTextureView(@Unsigned byte _stage, UniformHandle _sampler, TextureHandle _handle, @Unsigned short _firstLayer, @Unsigned short _numLayers, @Unsigned byte _firstMip, @Unsigned byte _numMips, @Unsigned int _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_TEXTURE_VIEW.invokeExact(segment(), _stage, _sampler.allocate(arena), _handle.allocate(arena), _firstLayer, _numLayers, _firstMip, _numMips, _flags);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Submit an empty primitive for rendering. Uniforms and draw state
	 * will be applied but no geometry will be submitted. Useful in cases
	 * when no other draw/compute primitive is submitted to view, but it's
	 * desired to execute clear view.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   These empty draw calls will sort before ordinary draw calls.
	 * @param _id View id.
	 */
	public final void touch(short _id) {
		try {
			MH_ENCODER_TOUCH.invokeExact(segment(), _id);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Submit primitive for rendering.
	 * @param _id View id.
	 * @param _program Program.
	 * @param _depth Depth for sorting.
	 * @param _flags Discard or preserve states. See {@code BGFX_DISCARD_*}.
	 */
	public final void submit(short _id, ProgramHandle _program, @Unsigned int _depth, @Unsigned byte _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SUBMIT.invokeExact(segment(), _id, _program.allocate(arena), _depth, _flags);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Submit primitive with occlusion query for rendering.
	 * @param _id View id.
	 * @param _program Program.
	 * @param _occlusionQuery Occlusion query.
	 * @param _depth Depth for sorting.
	 * @param _flags Discard or preserve states. See {@code BGFX_DISCARD_*}.
	 */
	public final void submitOcclusionQuery(short _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, @Unsigned int _depth, @Unsigned byte _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SUBMIT_OCCLUSION_QUERY.invokeExact(segment(), _id, _program.allocate(arena), _occlusionQuery.allocate(arena), _depth, _flags);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Submit primitive for rendering with index and instance data info from
	 * indirect buffer.
	 * <p>
	 * <strong>Attention:</strong> Availability depends on: {@code BGFX_CAPS_DRAW_INDIRECT}.
	 * @param _id View id.
	 * @param _program Program.
	 * @param _indirectHandle Indirect buffer.
	 * @param _start First element in indirect buffer.
	 * @param _num Number of draws.
	 * @param _depth Depth for sorting.
	 * @param _flags Discard or preserve states. See {@code BGFX_DISCARD_*}.
	 */
	public final void submitIndirect(short _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, @Unsigned int _start, @Unsigned int _num, @Unsigned int _depth, @Unsigned byte _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SUBMIT_INDIRECT.invokeExact(segment(), _id, _program.allocate(arena), _indirectHandle.allocate(arena), _start, _num, _depth, _flags);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Submit primitive for rendering with index and instance data info and
	 * draw count from indirect buffers.
	 * <p>
	 * <strong>Attention:</strong> Availability depends on: {@code BGFX_CAPS_DRAW_INDIRECT_COUNT}.
	 * @param _id View id.
	 * @param _program Program.
	 * @param _indirectHandle Indirect buffer.
	 * @param _start First element in indirect buffer.
	 * @param _numHandle Buffer for number of draws. Must be   created with {@code BGFX_BUFFER_INDEX32} and {@code BGFX_BUFFER_DRAW_INDIRECT}.
	 * @param _numIndex Element in number buffer.
	 * @param _numMax Max number of draws.
	 * @param _depth Depth for sorting.
	 * @param _flags Discard or preserve states. See {@code BGFX_DISCARD_*}.
	 */
	public final void submitIndirectCount(short _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, @Unsigned int _start, IndexBufferHandle _numHandle, @Unsigned int _numIndex, @Unsigned int _numMax, @Unsigned int _depth, @Unsigned byte _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SUBMIT_INDIRECT_COUNT.invokeExact(segment(), _id, _program.allocate(arena), _indirectHandle.allocate(arena), _start, _numHandle.allocate(arena), _numIndex, _numMax, _depth, _flags);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set compute index buffer.
	 * @param _stage Compute stage.
	 * @param _handle Index buffer handle.
	 * @param _access Buffer access. See {@code Access}.
	 */
	public final void setComputeIndexBuffer(@Unsigned byte _stage, IndexBufferHandle _handle, Access _access) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_COMPUTE_INDEX_BUFFER.invokeExact(segment(), _stage, _handle.allocate(arena), _access.ordinal());
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set compute vertex buffer.
	 * @param _stage Compute stage.
	 * @param _handle Vertex buffer handle.
	 * @param _access Buffer access. See {@code Access}.
	 */
	public final void setComputeVertexBuffer(@Unsigned byte _stage, VertexBufferHandle _handle, Access _access) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_COMPUTE_VERTEX_BUFFER.invokeExact(segment(), _stage, _handle.allocate(arena), _access.ordinal());
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set compute dynamic index buffer.
	 * @param _stage Compute stage.
	 * @param _handle Dynamic index buffer handle.
	 * @param _access Buffer access. See {@code Access}.
	 */
	public final void setComputeDynamicIndexBuffer(@Unsigned byte _stage, DynamicIndexBufferHandle _handle, Access _access) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_COMPUTE_DYNAMIC_INDEX_BUFFER.invokeExact(segment(), _stage, _handle.allocate(arena), _access.ordinal());
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set compute dynamic vertex buffer.
	 * @param _stage Compute stage.
	 * @param _handle Dynamic vertex buffer handle.
	 * @param _access Buffer access. See {@code Access}.
	 */
	public final void setComputeDynamicVertexBuffer(@Unsigned byte _stage, DynamicVertexBufferHandle _handle, Access _access) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_COMPUTE_DYNAMIC_VERTEX_BUFFER.invokeExact(segment(), _stage, _handle.allocate(arena), _access.ordinal());
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set compute indirect buffer.
	 * @param _stage Compute stage.
	 * @param _handle Indirect buffer handle.
	 * @param _access Buffer access. See {@code Access}.
	 */
	public final void setComputeIndirectBuffer(@Unsigned byte _stage, IndirectBufferHandle _handle, Access _access) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_COMPUTE_INDIRECT_BUFFER.invokeExact(segment(), _stage, _handle.allocate(arena), _access.ordinal());
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set compute image from texture.
	 * @param _stage Compute stage.
	 * @param _handle Texture handle.
	 * @param _mip Mip level.
	 * @param _access Image access. See {@code Access}.
	 * @param _format Texture format. See: {@code TextureFormat}.
	 */
	public final void setImage(@Unsigned byte _stage, TextureHandle _handle, @Unsigned byte _mip, Access _access, TextureFormat _format) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_IMAGE.invokeExact(segment(), _stage, _handle.allocate(arena), _mip, _access.ordinal(), _format.ordinal());
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Set compute image stage for draw primitive, selecting a sub-range of the
	 * texture's array layers and mip levels.
	 * @param _stage Compute stage.
	 * @param _handle Texture handle.
	 * @param _firstLayer First array layer.
	 * @param _numLayers Number of array layers.
	 * @param _mip Mip level.
	 * @param _access Image access. See {@code Access}.
	 * @param _format Texture format. See: {@code TextureFormat}.
	 */
	public final void setImageView(@Unsigned byte _stage, TextureHandle _handle, @Unsigned short _firstLayer, @Unsigned short _numLayers, @Unsigned byte _mip, Access _access, TextureFormat _format) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_SET_IMAGE_VIEW.invokeExact(segment(), _stage, _handle.allocate(arena), _firstLayer, _numLayers, _mip, _access.ordinal(), _format.ordinal());
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Dispatch compute.
	 * @param _id View id.
	 * @param _program Compute program.
	 * @param _numX Number of groups X.
	 * @param _numY Number of groups Y.
	 * @param _numZ Number of groups Z.
	 * @param _flags Discard or preserve states. See {@code BGFX_DISCARD_*}.
	 */
	public final void dispatch(short _id, ProgramHandle _program, @Unsigned int _numX, @Unsigned int _numY, @Unsigned int _numZ, @Unsigned byte _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_DISPATCH.invokeExact(segment(), _id, _program.allocate(arena), _numX, _numY, _numZ, _flags);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Dispatch compute indirect.
	 * @param _id View id.
	 * @param _program Compute program.
	 * @param _indirectHandle Indirect buffer.
	 * @param _start First element in indirect buffer.
	 * @param _num Number of dispatches.
	 * @param _flags Discard or preserve states. See {@code BGFX_DISCARD_*}.
	 */
	public final void dispatchIndirect(short _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, @Unsigned int _start, @Unsigned int _num, @Unsigned byte _flags) {
		try {
			try (Arena arena = Arena.ofConfined()) {
				MH_ENCODER_DISPATCH_INDIRECT.invokeExact(segment(), _id, _program.allocate(arena), _indirectHandle.allocate(arena), _start, _num, _flags);
			}
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Discard previously set state for draw or compute call.
	 * @param _flags Discard or preserve states. See {@code BGFX_DISCARD_*}.
	 */
	public final void discard(@Unsigned byte _flags) {
		try {
			MH_ENCODER_DISCARD.invokeExact(segment(), _flags);
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Blit texture region between two textures.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   The copy covers the region the two sides have in common: each side gives
	 *   the origin it starts at, and the size is the smaller of the two extents.
	 *   A zero {@code width}, {@code height} or {@code depth} extends to the rest of that mip.
	 * <p>
	 *   Blit is performed on GPU, and it is ordered within the view. In views, all
	 *   draw commands are executed after blit and compute commands.
	 * <p>
	 * <strong>Attention:</strong> Destination texture must be created with {@code BGFX_TEXTURE_BLIT_DST} flag.
	 * @param _id View id.
	 * @param _dst Destination texture region.
	 * @param _src Source texture region.
	 */
	public final void blit(short _id, TextureRegion _dst, TextureRegion _src) {
		try {
			MH_ENCODER_BLIT.invokeExact(segment(), _id, address(_dst), address(_src));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Blit buffer region between two buffers.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   The source region gives the number of bytes copied, and the destination
	 *   region gives only the offset they land at. A zero {@code size} copies the rest of
	 *   the source buffer. {@code rowPitch} and {@code slicePitch} are unused.
	 * <p>
	 *   Buffer blit is performed on GPU, and it is ordered within the view, same as
	 *   texture blit. In views, all draw commands are executed after blit and compute
	 *   commands.
	 * <p>
	 * <strong>Attention:</strong> Source buffer must be created with one of {@code BGFX_BUFFER_COMPUTE_*}, or
	 *   {@code BGFX_BUFFER_DRAW_INDIRECT} flags.
	 * <strong>Attention:</strong> Destination buffer must be created with {@code BGFX_BUFFER_COMPUTE_WRITE}, or
	 *   {@code BGFX_BUFFER_DRAW_INDIRECT} flag.
	 * <strong>Attention:</strong> Source and destination buffer must be different.
	 * @param _id View id.
	 * @param _dst Destination buffer region.
	 * @param _src Source buffer region.
	 */
	public final void blitBuffer(short _id, BufferRegion _dst, BufferRegion _src) {
		try {
			MH_ENCODER_BLIT_BUFFER.invokeExact(segment(), _id, address(_dst), address(_src));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Blit texture region into buffer.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   The texture region gives the size of the copy. {@code BufferRegion.rowPitch} and
	 *   {@code slicePitch} choose how the texels are laid out in the buffer, and 0 packs
	 *   them tightly. {@code BufferRegion.init} fills in the layout the backend copies
	 *   fastest, and bgfx repacks internally for any other layout.
	 * <p>
	 *   Blit is performed on GPU, and it is ordered within the view, same as texture
	 *   blit. In views, all draw commands are executed after blit and compute commands.
	 * <p>
	 * <strong>Attention:</strong> Destination buffer must be created with {@code BGFX_BUFFER_COMPUTE_WRITE}, or
	 *   {@code BGFX_BUFFER_DRAW_INDIRECT} flag.
	 * @param _id View id.
	 * @param _dst Destination buffer region.
	 * @param _src Source texture region.
	 */
	public final void blitToBuffer(short _id, BufferRegion _dst, TextureRegion _src) {
		try {
			MH_ENCODER_BLIT_TO_BUFFER.invokeExact(segment(), _id, address(_dst), address(_src));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Blit buffer contents into texture region.
	 * <p>
	 * <strong>Remarks:</strong> 
	 *   The texture region gives the size of the copy. {@code BufferRegion.rowPitch} and
	 *   {@code slicePitch} describe how the texels are laid out in the buffer, and 0 reads
	 *   them tightly packed. {@code BufferRegion.init} fills in the layout the backend
	 *   copies fastest, and bgfx repacks internally for any other layout.
	 * <p>
	 *   Blit is performed on GPU, and it is ordered within the view, same as texture
	 *   blit. In views, all draw commands are executed after blit and compute commands.
	 * <p>
	 * <strong>Attention:</strong> Source buffer must be created with one of {@code BGFX_BUFFER_COMPUTE_*}, or
	 *   {@code BGFX_BUFFER_DRAW_INDIRECT} flags.
	 * <strong>Attention:</strong> Destination texture must be created with {@code BGFX_TEXTURE_BLIT_DST} flag.
	 * @param _id View id.
	 * @param _dst Destination texture region.
	 * @param _src Source buffer region.
	 */
	public final void blitFromBuffer(short _id, TextureRegion _dst, BufferRegion _src) {
		try {
			MH_ENCODER_BLIT_FROM_BUFFER.invokeExact(segment(), _id, address(_dst), address(_src));
		} catch (Throwable ex) {
			throw invocationFailure(ex);
		}
	}
}
