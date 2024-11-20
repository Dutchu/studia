package org.example.toString;

import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.function.Function;
import java.util.stream.Collectors;

@FunctionalInterface
interface MethodToStringMapper {
    String map(Method method) throws Exception;
}

public class ToString {
    @Override
    public String toString() {
        Class<?> clazz = this.getClass();

        MethodToStringMapper methodMapper = method ->
                method.getName().substring(3)
                        + ": "
                        + method.invoke(this);

        return Arrays.stream(clazz.getMethods())
                .filter(this::isGetter)
                .map(wrapCheckedException(methodMapper))
                .map(Object::toString)
                .collect(Collectors.joining("\t"));

    }

    private boolean isGetter(Method method) {
        return method.getName().startsWith("get")
                && method.getParameterCount() == 0
                && !void.class.equals(method.getReturnType());
    }

    private <T, R> Function<T, R> wrapCheckedException(MethodToStringMapper mapper) {
        return method -> {
            try {
                return (R) mapper.map((Method) method);
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        };
    }
}
