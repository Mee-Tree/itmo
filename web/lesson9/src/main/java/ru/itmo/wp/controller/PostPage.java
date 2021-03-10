package ru.itmo.wp.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;
import ru.itmo.wp.domain.Comment;
import ru.itmo.wp.security.Guest;
import ru.itmo.wp.service.PostService;

import javax.servlet.http.HttpSession;
import javax.validation.Valid;

@Controller
@RequestMapping("/post")
public class PostPage extends Page {
    private final PostService postService;

    public PostPage(PostService postService) {
        this.postService = postService;
    }

    @Guest
    @GetMapping("/{stringId}")
    public String post(@PathVariable String stringId, Model model) {
        Long id = tryParseId(stringId);
        model.addAttribute("viewedPost", postService.findById(id));
        model.addAttribute("comment", new Comment());
        return "PostPage";
    }

    @PostMapping("/{stringId}")
    public String post(@PathVariable String stringId,
                       @Valid @ModelAttribute("comment") Comment comment,
                       BindingResult bindingResult,
                       HttpSession httpSession,
                       Model model) {
        Long id = tryParseId(stringId);

        if (bindingResult.hasErrors()) {
            model.addAttribute("viewedPost", postService.findById(id));
            return "PostPage";
        }

        comment.setUser(getUser(httpSession));
        postService.writeComment(id, comment);
        putMessage(httpSession, "Your comment has been published");

        return "redirect:{stringId}";
    }
}
