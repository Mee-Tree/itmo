package ru.itmo.wp.model.repository.impl;

import com.google.common.reflect.TypeToken;
import ru.itmo.wp.model.database.DatabaseUtils;
import ru.itmo.wp.model.domain.Entity;
import ru.itmo.wp.model.exception.RepositoryException;

import javax.sql.DataSource;
import java.sql.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public abstract class BasicRepositoryImpl<T extends Entity> {
    private final DataSource DATA_SOURCE = DatabaseUtils.getDataSource();

    @SuppressWarnings("UnstableApiUsage")
    private final String entityName = new TypeToken<T>(getClass()) {}.getRawType().getSimpleName();

    public T find(long id) {
        return findBy("id", id);
    }

    protected T findBy(String columnName, Object columnValue) {
        return findBy(Collections.singletonMap(columnName, columnValue));
    }

    protected T findBy(Map<String, Object> columns) {
        try (Connection connection = DATA_SOURCE.getConnection()) {
            String stringStatement = "SELECT * FROM " + entityName + " WHERE " + columns.keySet().stream()
                    .map(column -> column + "=?")
                    .collect(Collectors.joining(" AND "));
            try (PreparedStatement statement = connection.prepareStatement(stringStatement)) {
                setStrings(statement, columns.values().toArray());
                try (ResultSet resultSet = statement.executeQuery()) {
                    return toEntity(statement.getMetaData(), resultSet);
                }
            }
        } catch (SQLException e) {
            throw new RepositoryException(String.format("Can't find %s.", entityName), e);
        }
    }

    protected long findLong(String aggregateFunction) {
        return findLongWhere(aggregateFunction, "");
    }

    protected long findLongWhere(String aggregateFunction, String whereClause, Object... values) {
        try (Connection connection = DATA_SOURCE.getConnection()) {
            try (PreparedStatement statement = connection.prepareStatement(
                    "SELECT " + aggregateFunction + "(*) FROM " + entityName +
                        " WHERE " + (whereClause.isEmpty() ? "TRUE" : whereClause)
            )) {
                setStrings(statement, values);
                try (ResultSet resultSet = statement.executeQuery()) {
                    resultSet.next();
                    return resultSet.getLong(1);
                }
            }
        } catch (SQLException e) {
            throw new RepositoryException(String.format("Can't find %s.", entityName), e);
        }
    }

    protected List<T> findList() {
        return findListWhere("");
    }

    protected List<T> findListWhere(String whereClause, Object... values) {
        List<T> entities = new ArrayList<>();
        try (Connection connection = DATA_SOURCE.getConnection()) {
            try (PreparedStatement statement = connection.prepareStatement(
                    "SELECT * FROM " + entityName +
                        " WHERE " + (whereClause.isEmpty() ? "TRUE" : whereClause) +
                        " ORDER BY id DESC")) {
                setStrings(statement, values);

                try (ResultSet resultSet = statement.executeQuery()) {
                    T entity;
                    while ((entity = toEntity(statement.getMetaData(), resultSet)) != null) {
                        entities.add(entity);
                    }
                }
            }
        } catch (SQLException e) {
            throw new RepositoryException(String.format("Can't find %s.", entityName), e);
        }
        return entities;
    }

    public List<T> findAll() {
        return findList();
    }

    public long findCount() {
        return findLong("COUNT");
    }

    @SuppressWarnings("SqlResolve")
    protected void save(T entity, Map<String, Object> columns) {
        try (Connection connection = DATA_SOURCE.getConnection()) {
            String stringStatement =
                    "INSERT INTO " + entityName +
                        " (" + String.join(", ", columns.keySet()) + ", creationTime) " +
                    "VALUES (" + String.join(", ", getPlaceholders(columns.size())) + ", NOW())";

            try (PreparedStatement statement = connection.prepareStatement(
                    stringStatement, Statement.RETURN_GENERATED_KEYS)) {
                setStrings(statement, columns.values().toArray());

                if (statement.executeUpdate() != 1) {
                    throw new RepositoryException(String.format("Can't save %s.", entityName));
                } else {
                    ResultSet generatedKeys = statement.getGeneratedKeys();
                    if (generatedKeys.next()) {
                        entity.setId(generatedKeys.getLong(1));
                        entity.setCreationTime(find(entity.getId()).getCreationTime());
                    } else {
                        throw new RepositoryException(
                                String.format("Can't save %s [no autogenerated fields].", entityName));
                    }
                }
            }
        } catch (SQLException e) {
            throw new RepositoryException(String.format("Can't save %s.", entityName), e);
        }
    }

    private List<String> getPlaceholders(int size) {
        return Collections.nCopies(size, "?");
    }

    private void setStrings(PreparedStatement statement, Object... values) throws SQLException {
        int index = 1;
        for (Object value : values) {
            statement.setString(index++, String.valueOf(value));
        }
    }

    protected abstract T toEntity(ResultSetMetaData metaData, ResultSet resultSet) throws SQLException;
}
