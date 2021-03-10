package ru.itmo.wp.model.repository.impl;

import com.google.common.collect.ImmutableMap;
import ru.itmo.wp.model.domain.User;
import ru.itmo.wp.model.repository.UserRepository;

import java.sql.*;

public class UserRepositoryImpl extends BasicRepositoryImpl<User> implements UserRepository {

    @Override
    public User findByLogin(String login) {
        return findBy("login", login);
    }

    @Override
    public User findByEmail(String email) {
        return findBy("email", email);
    }

    @Override
    public User findByLoginAndPasswordSha(String login, String passwordSha) {
        return findBy(ImmutableMap.of("login", login, "passwordSha", passwordSha));
    }

    @Override
    public User findByEmailAndPasswordSha(String email, String passwordSha) {
        return findBy(ImmutableMap.of("email", email, "passwordSha", passwordSha));
    }

    @Override
    public void save(User user, String passwordSha) {
        super.save(user, ImmutableMap.of(
                "login", user.getLogin(),
                "email", user.getEmail(),
                "passwordSha", passwordSha));
    }

    protected User toEntity(ResultSetMetaData metaData, ResultSet resultSet) throws SQLException {
        if (!resultSet.next()) {
            return null;
        }

        User user = new User();
        for (int i = 1; i <= metaData.getColumnCount(); i++) {
            switch (metaData.getColumnName(i)) {
                case "id":
                    user.setId(resultSet.getLong(i));
                    break;
                case "login":
                    user.setLogin(resultSet.getString(i));
                    break;
                case "email":
                    user.setEmail(resultSet.getString(i));
                    break;
                case "creationTime":
                    user.setCreationTime(resultSet.getTimestamp(i));
                    break;
                default:
                    // No operations.
            }
        }

        return user;
    }
}
