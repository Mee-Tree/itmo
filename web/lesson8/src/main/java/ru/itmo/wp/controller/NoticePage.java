package ru.itmo.wp.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import ru.itmo.wp.form.NoticeForm;

import javax.servlet.http.HttpSession;
import javax.validation.Valid;

@Controller
@RequestMapping("/notice")
public class NoticePage extends Page {
    @GetMapping("/add")
    public String notice(Model model) {
        model.addAttribute("noticeForm", new NoticeForm());
        return "NoticePage";
    }

    @PostMapping("/add")
    public String notice(@Valid @ModelAttribute("noticeForm") NoticeForm noticeForm,
                        BindingResult bindingResult,
                        HttpSession httpSession) {
        if (bindingResult.hasErrors()) {
            return "NoticePage";
        }

        getNoticeService().add(noticeForm);
        putMessage(httpSession, "Notice has been successfully created");
        return "redirect:add";
    }
}
