package io.github.bkaradzic.bgfx.util;

public class NativeInvocationFailureException extends RuntimeException {
	public NativeInvocationFailureException(String message) {
		super(message);
	}

	public NativeInvocationFailureException(String message, Throwable cause) {
		super(message, cause);
	}

	public NativeInvocationFailureException(Throwable cause) {
		super(cause);
	}

	public NativeInvocationFailureException() {
		super();
	}
}
