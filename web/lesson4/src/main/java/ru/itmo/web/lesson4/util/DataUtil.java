package ru.itmo.web.lesson4.util;

import ru.itmo.web.lesson4.model.Color;
import ru.itmo.web.lesson4.model.Post;
import ru.itmo.web.lesson4.model.User;

import javax.servlet.http.HttpServletRequest;
import java.util.Arrays;
import java.util.List;
import java.util.Map;

public class DataUtil {
    private static final List<User> USERS = Arrays.asList(
            new User(1, "MikeMirzayanov", "Mike Mirzayanov", Color.BLUE),
            new User(6, "pashka", "Pavel Mavrin", Color.RED),
            new User(9, "geranazarov555", "Georgiy Nazarov", Color.GREEN),
            new User(11, "tourist", "Gennady Korotkevich", Color.RED)
    );

    private static final List<Post> POSTS = Arrays.asList(
            new Post(1,
                    "What is Codeforces?",
                    "<img alt=\"Codeforces Beta\" src=\"../img/cf-beta.png\" align=\"left\"/>" +
                        "<p>I noticed long ago, that all the websites about computer programming contests work on Web 1.0 principles. But the 21st century has come, the 30th International Programming Contest took place, and Google celebrated its 10th anniversary. Something has to be done! As Software-as-a-Service is conquering the world, contests administrators are still copying tests into judge systems. Something has to be done!</p>" +
                        "<p>Codeforces' aim is to offer you a convenient platform to organize, run and discuss programming contests. It will be a bit of a social network website, more than a news portal and more than an online judge. Being absolutely independent from me, you will be able to organize and run a contest. You will decide on your own if to make it open to the whole world or if it will be a contest for your University only. And if you're not interested in this, you might discuss the news in the contest world - read/write blogs, discuss topics, and support your dearest and nearest.</p>" +
                        "<p>Moreover, I plan to run regular contests according to new and interesting rules. Closer to the end of February I will be able to run the first beta-contests.</p>" +
                        "<p>But it's about the future, and now I suggest to go to Harbin together with the Saratov State University team. I will be writing a blog about our trip. I hope it will be interesting.</p>" +
                        "<p>For sure, you will find out, that many important features are missing there. It's because we're still working on it. Be patient, please. I will be glad to read your comments about what and how should be done. I can't promise that I'll be working on the system during the trip, but I'll go on working when we come back.</p>",
                    1),
            new Post(3,
                    "Do you know that?",
                    "<img alt=\"Reading\" src=\"../img/reading.png\" align=\"left\"/>" +
                        "<p>If you write solutions on C++ it regularly happens than input reading through std::cin appears to be slow because of the large input size. Certainly is more correct in such cases to write data reading more effectively - at least using scanf. But if the testing system uses GNU C++ (checked on MinGW 4.4.1, but I think it works on other versions too), and you don't want to rewrite input reading, it is possible to improve performance by only one line placed in the beginning of the program: <code>ios_base::sync_with_stdio(0)</code>.</p>" +
                        "<p>On my example where it was required to find the sum of one million integers, it has accelerated the program in 4.5 times. Tried to do the same test on MS Visual C ++ 9.0 - but it hasn't accelerated the reading.</p>",
                    1),
            new Post(420,
                    "ITMO Algorithms Course",
                    "<p>Hello Codeforces!</p>" +
                        "<p>I teach a course on algorithms and data structures at ITMO University. During the last year I was streaming all my lectures on <a href=\"https://twitch.tv/pmavrin\">Twitch</a> and uploaded the videos on <a href=\"https://www.youtube.com/pavelmavrin\">Youtube</a>.</p>" +
                        "<p>This year I want to try to do it in English. </p>" +
                        "<p>This is a four-semester course. The rough plan for the first semester:</p>" +
                        "<ul>" +
                        "   <li>Algorithms, complexity, asymptotics</li>" +
                        "   <li>Sorting algorithms</li>" +
                        "   <li>Binary heap</li>" +
                        "   <li>Binary search</li>" +
                        "   <li>Linked lists, Stack, Queue</li>" +
                        "   <li>Amortized analysis</li>" +
                        "   <li>Fibonacci Heap</li>" +
                        "   <li>Disjoint Set Union</li>" +
                        "   <li>Dynamic Programming</li>" +
                        "   <li>Hash Tables</li> " +
                        "</ul>" +
                        "<p>The lectures are open for everybody. If you want to attend, please fill out <a href=\"https://docs.google.com/forms/d/e/1FAIpQLSfHIhiwAUyKfnt92NluNj2tLnczp0oxu5szPS4S_PF3N7EUDA/viewform\">this form</a> to help me pick the optimal day and time. </p>" +
                        "<p>See you!</p>",
                    6)
    );

    public static void addData(HttpServletRequest request, Map<String, Object> data) {
        data.put("users", USERS);
        data.put("posts", POSTS);

        for (User user : USERS) {
            if (Long.toString(user.getId()).equals(request.getParameter("logged_user_id"))) {
                data.put("user", user);
            }
        }
    }
}
