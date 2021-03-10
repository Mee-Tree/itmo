<#-- @ftlvariable name="myArticles" type="ru.itmo.wp.model.domain.Article[]" -->
<#import "commons.ftlh" as c>

<@c.page>
    <div class="my-articles datatable">
        <div class="caption">My Articles</div>
        <table>
            <thead>
            <tr>
                <th>Id</th>
                <th>Title</th>
                <th>Hide/Show</th>
            </tr>
            </thead>
            <tbody>
            <#list myArticles as article>
            <tr>
                <td>${article.id}</td>
                <td>${article.title}</td>
                <td><input class="hide-btn" id="${article.id}" type="submit"
                           value="${article.hidden?then("Show", "Hide")}">
                </td>
            </tr>
            </#list>
            </tbody>
        </table>
    </div>

    <script>
        $(function () {
            $(".my-articles .hide-btn").click(function() {
                const $btn = $(this);
                $btn.attr("disabled", true);
                const hidden = !($btn.val() === "Show");

                ajax({
                    action: "changeVisibility",
                    id: $btn.attr("id"),
                    hidden,
                    success: function (response) {
                        if (response["error"]) {
                            notify(response["error"], "error");
                        }

                        if (hidden) {
                            notify("Only you can see this article now");
                            $btn.val("Show");
                        } else {
                            notify("Everyone can see this article now");
                            $btn.val("Hide");
                        }
                        $btn.attr("disabled", false);
                    }
                })
            });
        })
    </script>
</@c.page>
