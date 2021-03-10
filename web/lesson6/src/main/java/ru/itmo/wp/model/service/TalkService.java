package ru.itmo.wp.model.service;

import ru.itmo.wp.model.domain.Talk;
import ru.itmo.wp.model.domain.User;
import ru.itmo.wp.model.repository.TalkRepository;
import ru.itmo.wp.model.repository.impl.TalkRepositoryImpl;

import java.util.List;

public class TalkService {
    private final TalkRepository talkRepository = new TalkRepositoryImpl();

    public void sendMessage(User user, long targetSourceId, String text) {
        Talk talk = new Talk();
        talk.setSourceUserId(user.getId());
        talk.setTargetUserId(targetSourceId);
        talk.setText(text);
        talkRepository.save(talk);
    }

    public List<Talk> findTalks(User user) {
        return talkRepository.findByUserId(user.getId());
    }
}
