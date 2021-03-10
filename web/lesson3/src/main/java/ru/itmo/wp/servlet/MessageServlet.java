package ru.itmo.wp.servlet;

import com.google.gson.Gson;
import ru.itmo.wp.model.Message;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

public class MessageServlet extends HttpServlet {
    public static final Charset UTF_8 = StandardCharsets.UTF_8;
    public static final Gson GSON = new Gson();

    private final List<Message> messages = new CopyOnWriteArrayList<>();

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession();

        switch (request.getRequestURI()) {
            case "/message/auth":
                String user = request.getParameter("user");
                if (session.getAttribute("user") == null && user != null) {
                    session.setAttribute("user", user);
                }
                writeJson(response, user);
                break;
            case "/message/add":
                String text = request.getParameter("text");
                user = (String) request.getSession().getAttribute("user");
                if (user != null && text != null && !text.isEmpty()) {
                    messages.add(new Message(user, text));
                }
                break;
            case "/message/findAll":
                writeJson(response, messages);
                break;
            default:
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private void writeJson(HttpServletResponse response, Object object) throws IOException {
        response.setCharacterEncoding(UTF_8.name());
        response.setContentType("application/json");
        PrintWriter responseWriter = new PrintWriter(response.getOutputStream(),
                false, UTF_8);
        responseWriter.print(GSON.toJson(object));
        responseWriter.flush();
    }
}
