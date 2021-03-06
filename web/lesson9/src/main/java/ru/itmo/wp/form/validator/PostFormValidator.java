package ru.itmo.wp.form.validator;

import org.springframework.stereotype.Component;
import org.springframework.validation.Errors;
import org.springframework.validation.Validator;
import ru.itmo.wp.form.PostForm;
import ru.itmo.wp.service.TagService;

import java.util.List;

@Component
public class PostFormValidator implements Validator {

    public boolean supports(Class<?> clazz) {
        return PostForm.class.equals(clazz);
    }

    public void validate(Object target, Errors errors) {
        if (!errors.hasErrors()) {
            PostForm postForm = (PostForm) target;
            List<String> tagNames = TagService.splitStringNames(postForm);

            if (tagNames.stream().anyMatch(name -> !TagService.isValidName(name))) {
                errors.rejectValue("tags", "tags.invalid-tag",
                        "one or more tags are invalid");
            }
        }
    }
}
