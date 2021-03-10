package ru.itmo.wp.service;

import org.springframework.stereotype.Service;
import ru.itmo.wp.form.PostForm;

import java.util.Arrays;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

@Service
public class TagService {
    public static final String NAME_SEPARATOR = "\\s+";

    public static boolean isValidName(String name) {
        return name.matches("[a-zA-Z]*") && name.length() < 20;
    }

    public static List<String> splitStringNames(PostForm postForm) {
        return Arrays.stream(postForm.getTags().split(NAME_SEPARATOR))
                .filter(name -> !name.isEmpty())
                .distinct()
                .collect(Collectors.toList());
    }
}
