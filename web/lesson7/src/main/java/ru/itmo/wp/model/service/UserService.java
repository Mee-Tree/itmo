package ru.itmo.wp.model.service;

import com.google.common.base.CharMatcher;
import com.google.common.base.Strings;
import com.google.common.hash.Hashing;
import ru.itmo.wp.model.domain.User;
import ru.itmo.wp.model.exception.ValidationException;
import ru.itmo.wp.model.repository.UserRepository;
import ru.itmo.wp.model.repository.impl.UserRepositoryImpl;

import java.nio.charset.StandardCharsets;
import java.util.List;

/** @noinspection UnstableApiUsage*/
public class UserService extends Service {
    private final UserRepository userRepository = new UserRepositoryImpl();
    private static final String PASSWORD_SALT = "177d4b5f2e4f4edafa7404533973c04c513ac619";

    public void validateRegistration(User user, String password) throws ValidationException {
        if (Strings.isNullOrEmpty(user.getLogin())) {
            throw new ValidationException("Login is required");
        }
        if (!user.getLogin().matches("[a-z]+")) {
            throw new ValidationException("Login can contain only lowercase Latin letters");
        }
        if (user.getLogin().length() > 8) {
            throw new ValidationException("Login can't be longer than 8 letters");
        }
        if (userRepository.findByLogin(user.getLogin()) != null) {
            throw new ValidationException("Login is already in use");
        }

        if (Strings.isNullOrEmpty(user.getEmail())) {
            throw new ValidationException("Email is required");
        }
        if (!isValidEmail(user.getEmail())) {
            throw new ValidationException("Incorrect email");
        }
        if (userRepository.findByEmail(user.getEmail()) != null) {
            throw new ValidationException("Email is already in use");
        }

        if (Strings.isNullOrEmpty(password)) {
            throw new ValidationException("Password is required");
        }
        if (password.length() < 4) {
            throw new ValidationException("Password can't be shorter than 4 characters");
        }
        if (password.length() > 12) {
            throw new ValidationException("Password can't be longer than 12 characters");
        }
    }

    public void validatePrivilegesChange(User currentUser, String stringId, String stringAdmin) throws ValidationException {
        if (Strings.isNullOrEmpty(stringId)) {
            throw new ValidationException("User id is required");
        }
        if (!isLong(stringId)) {
            throw new ValidationException("User id must be a number");
        }

        if (Strings.isNullOrEmpty(stringAdmin)) {
            throw new ValidationException("Parameter 'admin' is required");
        }
        if (!isBoolean(stringAdmin)) {
            throw new ValidationException("Admin must be a boolean");
        }

        User user = find(Long.parseLong(stringId));
        if (user == null) {
            throw new ValidationException("There's no such user");
        }
        if (!currentUser.isAdmin()) {
            throw new ValidationException("You have no rights to grant admin rights");
        }
        if (user.isAdmin() == Boolean.parseBoolean(stringAdmin)) {
            throw new ValidationException("This user already has the rights you trying to grant him");
        }
    }

    public User validateAndFindByLoginOrEmailAndPassword(String loginOrEmail, String password)
            throws ValidationException {
        User user = userRepository.findByLoginOrEmailAndPasswordSha(loginOrEmail, getPasswordSha(password));
        if (user == null) {
            throw new ValidationException("Invalid login or password");
        }
        return user;
    }

    public boolean isValidEmail(String email) {
        return CharMatcher.is('@').countIn(email) == 1;
    }

    public void register(User user, String password) {
        userRepository.save(user, getPasswordSha(password));
    }

    private String getPasswordSha(String password) {
        return Hashing.sha256().hashBytes((PASSWORD_SALT + password).getBytes(StandardCharsets.UTF_8)).toString();
    }

    public User find(long id) {
        return userRepository.find(id);
    }

    public List<User> findAll() {
        return userRepository.findAll();
    }

    public void changePrivileges(long id, boolean admin) {
        User user = find(id);
        user.setAdmin(admin);
        userRepository.update(user);
    }

    public boolean isAdmin(long id) {
        User user = find(id);
        return user != null && user.isAdmin();
    }
}
