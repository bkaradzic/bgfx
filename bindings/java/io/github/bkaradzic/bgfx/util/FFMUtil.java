// Copyright 2011-2026 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE

package io.github.bkaradzic.bgfx.util;

import java.lang.foreign.*;
import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodHandles;
import java.lang.invoke.MethodType;
import java.lang.invoke.MutableCallSite;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

import org.jspecify.annotations.NullMarked;
import org.jspecify.annotations.Nullable;

/**
 * Shared Java FFM support used by the generated bgfx binding.
 */
@NullMarked
@SuppressWarnings("restricted")
public final class FFMUtil {
	/**
	 * Native linker used for bgfx downcalls and callback upcalls.
	 */
	public static final Linker LINKER = Linker.nativeLinker();
	private static final SymbolLookup LIBRARY_LOOKUP = SymbolLookup.loaderLookup();


	/**
	 * Platform-native layout of C {@code uintptr_t}.
	 */
	public static final ValueLayout C_UINTPTR_T =
		(ValueLayout) LINKER.canonicalLayouts().get("size_t");

	private FFMUtil() {}

	private static MemorySegment symbol(String name) {
		return FFMUtil.LIBRARY_LOOKUP.find(name).orElseThrow(() -> new UnsatisfiedLinkError("Unable to find native symbol " + name));
	}



	/**
	 * Creates a fixed-arity native handle that links on its first invocation.
	 * @param name native symbol name
	 * @param descriptor native function descriptor
	 * @return a stable handle that resolves its native target on first use
	 */
	public static synchronized MethodHandle downcall(String name, FunctionDescriptor descriptor) {
		Objects.requireNonNull(name, "name");
		Objects.requireNonNull(descriptor, "descriptor");
		MethodType type = descriptor.toMethodType();
		if(descriptor.returnLayout().orElse(null) instanceof GroupLayout) {
			type = type.insertParameterTypes(0, SegmentAllocator.class);
		}
		MutableCallSite site = new MutableCallSite(type);
		try {
			MethodHandle resolver = MethodHandles.lookup().findStatic(FFMUtil.class, "linkDowncall",
				MethodType.methodType(MethodHandle.class, MutableCallSite.class, String.class, FunctionDescriptor.class));
			resolver = MethodHandles.insertArguments(resolver, 0, site, name, descriptor);
			site.setTarget(MethodHandles.collectArguments(MethodHandles.exactInvoker(type), 0, resolver));
		} catch(NoSuchMethodException | IllegalAccessException ex) {
			throw new ExceptionInInitializerError(ex);
		}
		return site.dynamicInvoker();
	}

	private static MethodHandle linkDowncall(MutableCallSite site, String name, FunctionDescriptor descriptor) {
		MethodHandle target = LINKER.downcallHandle(symbol(name), descriptor);
		site.setTarget(target);
		MutableCallSite.syncAll(new MutableCallSite[] {site});
		return target;
	}

	/**
	 * Creates a zero-argument handle that resolves a variadic symbol on first use.
	 * @param name native symbol name
	 * @return a stable handle returning the native symbol address
	 */
	public static synchronized MethodHandle variadicSymbol(String name) {
		Objects.requireNonNull(name, "name");
		MutableCallSite site = new MutableCallSite(MethodType.methodType(MemorySegment.class));
		try {
			MethodHandle resolver = MethodHandles.lookup().findStatic(FFMUtil.class, "linkVariadicSymbol",
				MethodType.methodType(MemorySegment.class, MutableCallSite.class, String.class));
			site.setTarget(MethodHandles.insertArguments(resolver, 0, site, name));
		} catch(NoSuchMethodException | IllegalAccessException ex) {
			throw new ExceptionInInitializerError(ex);
		}
		return site.dynamicInvoker();
	}

	private static MemorySegment linkVariadicSymbol(MutableCallSite site, String name) {
		MemorySegment address = symbol(name);
		site.setTarget(MethodHandles.constant(MemorySegment.class, address));
		MutableCallSite.syncAll(new MutableCallSite[] {site});
		return address;
	}

	public static synchronized void link() {
		throw new UnsupportedOperationException();
	}

	/**
	 * Invokes a C variadic entry point, inferring each variadic native layout
	 * from its Java value and applying C default argument promotions.
	 * Byte, short, character, boolean, integer, long, float, double, string,
	 * memory segment, native object, and enum values are supported.
	 *
	 * @param symbolHandle linked zero-argument symbol-address handle
	 * @param descriptor   descriptor of the fixed arguments and return value
	 * @param fixedArgs    converted fixed native arguments
	 * @param variadicArgs Java values to convert to promoted variadic arguments
	 * @return the native result, or {@code null} for {@code void}
	 */
	public static @Nullable Object invokeVariadic(MethodHandle symbolHandle, FunctionDescriptor descriptor, Object[] fixedArgs, Object[] variadicArgs) {
		Objects.requireNonNull(descriptor, "descriptor");
		Objects.requireNonNull(symbolHandle, "symbolHandle");
		Objects.requireNonNull(fixedArgs, "fixedArgs");
		Objects.requireNonNull(variadicArgs, "variadicArgs");
		MemoryLayout[] layouts = new MemoryLayout[variadicArgs.length];
		Object[] nativeArgs = Arrays.copyOf(fixedArgs, fixedArgs.length + variadicArgs.length);
		try(Arena arena = Arena.ofConfined()) {
			for(int i = 0; i < variadicArgs.length; ++i) {
				Object argument = Objects.requireNonNull(variadicArgs[i], "variadicArgs[" + i + "]");
				VarArgValue value = VarArgValue.of(argument, arena);
				layouts[i] = value.layout();
				nativeArgs[fixedArgs.length + i] = value.value();
			}
			FunctionDescriptor variadicDescriptor = descriptor.appendArgumentLayouts(layouts);
			MemorySegment symbol;
			try {
				symbol = (MemorySegment) symbolHandle.invokeExact();
			} catch(Throwable ex) {
				throw invocationFailure(ex);
			}
			MethodHandle handle = LINKER.downcallHandle(symbol, variadicDescriptor, Linker.Option.firstVariadicArg(fixedArgs.length));
			return invoke(handle, nativeArgs);
		}
	}

	private record VarArgValue(ValueLayout layout, Object value) {
		private static VarArgValue of(Object argument, Arena arena) {
			return switch(argument) {
				case Byte number -> new VarArgValue(ValueLayout.JAVA_INT, number.intValue());
				case Short number -> new VarArgValue(ValueLayout.JAVA_INT, number.intValue());
				case Character character -> new VarArgValue(ValueLayout.JAVA_INT, (int) character);
				case Boolean bool -> new VarArgValue(ValueLayout.JAVA_INT, bool ? 1 : 0);
				case Integer i -> new VarArgValue(ValueLayout.JAVA_INT, i);
				case Long l -> new VarArgValue(ValueLayout.JAVA_LONG, l);
				case Float number -> new VarArgValue(ValueLayout.JAVA_DOUBLE, number.doubleValue());
				case Double v -> new VarArgValue(ValueLayout.JAVA_DOUBLE, v);
				case String string -> new VarArgValue(ValueLayout.ADDRESS, cString(arena, string));
				case MemorySegment segment -> new VarArgValue(ValueLayout.ADDRESS, address(segment));
				case NativeObject object -> new VarArgValue(ValueLayout.ADDRESS, address(object));
				case Enum<?> enumValue -> new VarArgValue(ValueLayout.JAVA_INT, enumValue.ordinal());
				default -> throw new IllegalArgumentException("Unsupported C variadic argument type: " + argument.getClass().getName());
			};
		}
	}

	/**
	 * Resolves a virtual Java callback method for an upcall stub.
	 *
	 * @param owner callback interface
	 * @param name  callback method name
	 * @param type  callback method type
	 * @return the resolved callback target
	 */
	public static MethodHandle upcallTarget(Class<?> owner, String name, MethodType type) {
		try {
			return MethodHandles.lookup().findVirtual(owner, name, type);
		} catch(NoSuchMethodException | IllegalAccessException ex) {
			throw new ExceptionInInitializerError(ex);
		}
	}

	/**
	 * Invokes a native handle with dynamically supplied arguments.
	 *
	 * @param handle native method handle
	 * @param args   native arguments
	 * @return the native result, or {@code null} for {@code void}
	 */
	public static @Nullable Object invoke(MethodHandle handle, Object... args) {
		try {
			return handle.invokeWithArguments(args);
		} catch(Throwable ex) {
			throw invocationFailure(ex);
		}
	}

	/**
	 * Converts an unexpected method-handle failure to an unchecked exception.
	 *
	 * @param exception invocation failure
	 * @return the unchecked failure
	 */
	public static RuntimeException invocationFailure(Throwable exception) {
		if(exception instanceof RuntimeException runtime) {
			return runtime;
		}
		if(exception instanceof Error error) {
			throw error;
		}
		throw new NativeInvocationFailureException("Failed to invoke", exception);
	}

	/**
	 * Invokes a layout slice handle at offset zero.
	 *
	 * @param handle  layout slice handle
	 * @param segment containing segment
	 * @return the selected member segment
	 */
	public static MemorySegment slice(MethodHandle handle, MemorySegment segment) {
		try {
			return (MemorySegment) handle.invokeExact(segment, 0L);
		} catch(RuntimeException | Error ex) {
			throw ex;
		} catch(Throwable ex) {
			throw new AssertionError("Unexpected layout slice failure", ex);
		}
	}

	/**
	 * Creates a C-compatible structure layout with explicit ABI padding.
	 *
	 * @param name    native structure name
	 * @param members structure members in declaration order
	 * @return the padded structure layout
	 */
	public static StructLayout cStruct(String name, MemoryLayout... members) {
		List<MemoryLayout> elements = new ArrayList<>();
		long offset = 0;
		long alignment = 1;
		for(MemoryLayout member : members) {
			long memberAlignment = member.byteAlignment();
			long padding = (memberAlignment - offset % memberAlignment) % memberAlignment;
			if(padding != 0) {
				elements.add(MemoryLayout.paddingLayout(padding));
				offset += padding;
			}
			elements.add(member);
			offset += member.byteSize();
			alignment = Math.max(alignment, memberAlignment);
		}
		long padding = (alignment - offset % alignment) % alignment;
		if(padding != 0) {
			elements.add(MemoryLayout.paddingLayout(padding));
		}
		return MemoryLayout.structLayout(elements.toArray(MemoryLayout[]::new))
			.withByteAlignment(alignment)
			.withName(name);
	}

	/**
	 * Returns a segment view sized for the supplied native layout.
	 *
	 * @param segment source segment
	 * @param layout  required native layout
	 * @return a segment view with the layout size
	 */
	public static MemorySegment view(MemorySegment segment, MemoryLayout layout) {
		Objects.requireNonNull(segment, "segment");
		if(segment.address() == 0) {
			return MemorySegment.NULL;
		}
		if(segment.byteSize() == 0) {
			return segment.reinterpret(layout.byteSize());
		}
		if(segment.byteSize() < layout.byteSize()) {
			throw new IllegalArgumentException("Segment is smaller than " + layout);
		}
		return segment.asSlice(0, layout.byteSize());
	}

	/**
	 * Converts a nullable or zero-address segment to a canonical native address.
	 *
	 * @param segment nullable segment
	 * @return the segment, or {@link MemorySegment#NULL} when its address is zero
	 */
	public static MemorySegment address(@Nullable MemorySegment segment) {
		return segment == null || segment.address() == 0
			? MemorySegment.NULL
			: segment;
	}

	/**
	 * Converts a nullable or zero-address native object to a canonical address.
	 *
	 * @param object nullable native object
	 * @return the object's segment, or {@link MemorySegment#NULL} when its address is zero
	 */
	public static MemorySegment address(@Nullable NativeObject object) {
		return object == null ? MemorySegment.NULL : address(object.segment());
	}

	/**
	 * Allocates a nullable UTF-8 C string.
	 *
	 * @param allocator destination allocator
	 * @param value     nullable Java string
	 * @return the allocated C string or {@link MemorySegment#NULL}
	 */
	public static MemorySegment cString(SegmentAllocator allocator, @Nullable String value) {
		return value == null ? MemorySegment.NULL : allocator.allocateFrom(value);
	}

	/**
	 * Reads a nullable UTF-8 C string.
	 *
	 * @param address nullable C string address
	 * @return the Java string, or {@code null}
	 */
	public static @Nullable String readString(MemorySegment address) {
		return address.address() == 0 ? null : address.reinterpret(Long.MAX_VALUE).getString(0);
	}

	/**
	 * Converts a Java {@code long} to the platform-native {@code uintptr_t} carrier.
	 *
	 * @param value Java value
	 * @return the platform-native carrier value
	 */
	public static Object nativeUintptr(long value) {
		return C_UINTPTR_T.carrier() == long.class ? value : (int) value;
	}

	/**
	 * Converts the platform-native {@code uintptr_t} carrier to a Java {@code long}.
	 *
	 * @param value platform-native carrier value
	 * @return the Java value
	 */
	public static long javaUintptr(Object value) {
		return value instanceof Long val ? val : Integer.toUnsignedLong((Integer) value);
	}
}
