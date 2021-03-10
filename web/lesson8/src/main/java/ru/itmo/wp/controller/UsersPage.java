package ru.itmo.wp.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import ru.itmo.wp.form.ToggleForm;

import javax.servlet.http.HttpSession;
import javax.validation.Valid;

@Controller
@RequestMapping("/users")
public class UsersPage extends Page {
    @GetMapping("/all")
    public String users(Model model, HttpSession httpSession) {
        model.addAttribute("users", getUserService().findAll());
        return getUser(httpSession) != null
                ? "UsersPage"
                : "redirect:/enter";
    }

    @PostMapping("/all")
    public String toggle(@ModelAttribute("toggleForm") @Valid ToggleForm toggleForm,
                             BindingResult bindingResult,
                             HttpSession httpSession) {
        if (bindingResult.hasErrors() || getUser(httpSession) == null) {
            return "redirect:all";
        }

        if (toggleForm.getId() == getUser(httpSession).getId()) {
            putMessage(httpSession, "You cannot disable yourself");
            return "redirect:all";
        }

        getUserService().toggleDisabled(toggleForm);
        putMessage(httpSession, "This user has been " +
                toggleForm.getState().toLowerCase() + "d");
        return "redirect:all";
    }
}
