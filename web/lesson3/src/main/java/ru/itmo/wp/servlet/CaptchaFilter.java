package ru.itmo.wp.servlet;

import org.apache.commons.io.FileUtils;
import ru.itmo.wp.util.ImageUtils;

import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.http.HttpFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.Base64;
import java.util.Random;

public class CaptchaFilter extends HttpFilter {
    public static final Random RANDOM = new Random();

    @Override
    public void doFilter(HttpServletRequest request, HttpServletResponse response, FilterChain chain)
            throws IOException, ServletException {
        if (!"GET".equals(request.getMethod())) {
            chain.doFilter(request, response);
            return;
        }

        HttpSession session = request.getSession();
        String number = request.getParameter("number");
        Object captchaNumber = session.getAttribute("captcha-number");

        if (captchaNumber != null && String.valueOf(captchaNumber).equals(number)) {
            session.removeAttribute("captcha-number");
            session.setAttribute("captcha-passed", true);
            chain.doFilter(request, response);
        } else if (session.getAttribute("captcha-passed") == null) {
            session.setAttribute("captcha-number", generateCaptcha(response));
        } else {
            chain.doFilter(request, response);
        }
    }

    private int generateCaptcha(HttpServletResponse response) throws IOException {
        int number = 100 + RANDOM.nextInt(900);
        String encodedImg = new String(
                Base64.getEncoder().encode(ImageUtils.toPng(String.valueOf(number))));

        String captchaString = FileUtils.readFileToString(
                new File(getServletContext().getRealPath("static/captcha.html")), StandardCharsets.UTF_8);
        captchaString = captchaString.replace("$IMG", encodedImg);

        response.setContentType("text/html");
        PrintWriter responseWriter = response.getWriter();
        responseWriter.write(captchaString);
        responseWriter.flush();
        return number;
    }
}
