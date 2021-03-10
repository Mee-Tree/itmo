package ru.itmo.wp.controller;

import org.apache.commons.lang3.math.NumberUtils;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/user")
public class UserPage extends Page {
    @GetMapping("/{stringId}")
    public String user(@PathVariable String stringId, Model model) {
        long id = NumberUtils.toLong(stringId);
        model.addAttribute("viewedUser", getUserService().findById(id));
        return "UserPage";
    }
}
