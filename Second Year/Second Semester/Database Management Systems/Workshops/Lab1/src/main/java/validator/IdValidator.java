package validator;

public class IdValidator implements Validator<Integer> {
    @Override
    public void validate(Integer entity) {
        if (!isValid(entity)) {
            throw new IllegalArgumentException("Invalid ID");
        }
    }

    public static boolean isValid(Integer id) {
        return id > 0;
    }
}
