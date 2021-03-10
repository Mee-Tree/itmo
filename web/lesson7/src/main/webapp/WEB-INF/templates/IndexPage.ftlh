<#-- @ftlvariable name="users" type="ru.itmo.wp.model.domain.User[]" -->
<#import "commons.ftlh" as c>

<@c.page>
    <div class="articles">
        <div class="noData">No Data</div>
        <template>
            <article>
                <div class="title"></div>
                <div class="information"></div>
                <div class="body"></div>
                <ul class="attachment">
                    <li>Announcement of <a href="#">Codeforces Round #510 (Div. 1)</a></li>
                    <li>Announcement of <a href="#">Codeforces Round #510 (Div. 2)</a></li>
                </ul>
                <div class="footer">
                    <div class="left">
                        <img src="img/voteup.png" title="Vote Up" alt="Vote Up"/>
                        <span class="positive-score">+173</span>
                        <img src="img/votedown.png" title="Vote Down" alt="Vote Down"/>
                    </div>
                    <div class="right">
                        <img src="img/date_16x16.png" title="Publish Time" alt="Publish Time"/>
                        2 days ago
                        <img src="img/comments_16x16.png" title="Comments" alt="Comments"/>
                        <a href="#">68</a>
                    </div>
                </div>
            </article>
        </template>
    </div>
<script>
    $(function () {
        const $articles = $(".articles");
        const $noData = $articles.find(".noData");
        $noData.text("Loading...");

        ajax({
            action: "findAll",
            success: function(response) {
                response["articles"].forEach(function(article) {
                    $noData.hide();
                    const $tpl = $($articles.find("template").html()).clone();
                    $tpl.find(".title").text(article["title"]);
                    const user = response["userById"][article["userId"]];
                    $tpl.find(".information").text("By " + user.login + ", 2 days ago");
                    $tpl.find(".body").text(article["text"]);
                    $articles.append($tpl);
                });
            }
        });
    })

    $(function () {
        $("aside section").click(function () {
            $(this).css("background-color", "red");
        });
    })
</script>
</@c.page>
