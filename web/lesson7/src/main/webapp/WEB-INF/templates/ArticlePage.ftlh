<#-- @ftlvariable name="text" type="java.lang.String" -->
<#-- @ftlvariable name="title" type="java.lang.String" -->
<#-- @ftlvariable name="error" type="java.lang.String" -->
<#import "commons.ftlh" as c>

<@c.page>
    <div class="article form-box">
        <div class="header">Create an article</div>
        <div class="body">
            <form method="post" action="">
                <input type="hidden" name="action" value="addArticle"/>
                <div class="field">
                    <div class="name">
                        <label for="title">Title</label>
                    </div>
                    <div class="value">
                        <input id="title" name="title"/>
                    </div>
                </div>
                <div class="field">
                    <div class="name">
                        <label for="text">Text</label>
                    </div>
                    <div class="value">
                        <textarea id="text" name="text" maxlength="2000"
                                  rows="4" cols="25"></textarea>
                    </div>
                </div>
                <div class="field">
                    <div class="name">
                        <label for="hidden">Hidden?</label>
                    </div>
                    <div class="value">
                        <input id="hidden" name="hidden" type="checkbox">
                    </div>
                </div>
                <div class="error"></div>
                <div class="button-field">
                    <input type="submit" value="Create">
                </div>
            </form>
        </div>
    </div>

    <script>
        $(function () {
            $(".article form").submit(function () {
                const title = $(this).find("input[name='title']").val();
                const text = $(this).find("textarea[name='text']").val();
                const hidden = $(this).find("input[name='hidden']").is(":checked");
                const $error = $(this).find(".error");

                ajax({
                    action: "addArticle",
                    title,
                    text,
                    hidden,
                    success: function (response) {
                        if (response["error"]) {
                            $error.text(response["error"]);
                        } else {
                            notify("Your article has been successfully created");
                        }
                    }
                });

                return false;
            });
        })
    </script>
</@c.page>
