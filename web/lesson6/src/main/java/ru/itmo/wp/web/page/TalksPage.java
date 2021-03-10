package ru.itmo.wp.web.page;

import com.google.common.base.Strings;
import ru.itmo.wp.web.exception.RedirectException;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

@SuppressWarnings({"unused"})
public class TalksPage extends Page {

    @Override
    protected void before(HttpServletRequest request, Map<String, Object> view) {
        super.before(request, view);
        if (getUser() == null) {
            setMessage("You have to be authorised to use talks");
            throw new RedirectException("/index");
        }
        view.put("users", getUserService().findAll());
        view.put("talks", getTalkService().findTalks(getUser()));
    }

    private void sendMessage(HttpServletRequest request, Map<String, Object> view) {
        long targetSourceId = Long.parseLong(request.getParameter("targetUserId"));
        String text = request.getParameter("text");

        if (!Strings.isNullOrEmpty(text)) {
            getTalkService().sendMessage(getUser(), targetSourceId, text);
        }
        throw new RedirectException("/talks");
    }
}
