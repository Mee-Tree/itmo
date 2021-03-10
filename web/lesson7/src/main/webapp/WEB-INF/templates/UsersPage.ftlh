<#-- @ftlvariable name="user" type="ru.itmo.wp.model.domain.User" -->
<#-- @ftlvariable name="users" type="ru.itmo.wp.model.domain.User[]" -->
<#import "commons.ftlh" as c>

<@c.page>
    <div class="users datatable">
        <div class="caption">User</div>
        <table>
            <thead>
            <tr>
                <th>Id</th>
                <th>Login</th>
                <th class="admin" hidden>Admin</th>
            </tr>
            </thead>
            <tbody>
            <template>
                <tr>
                    <td class="user_id"></td>
                    <td class="user_login"></td>
                    <td class="user_admin" hidden>
                        <span></span>
                        <input class="button" type="submit">
                    </td>
                </tr>
            </template>
            <tr class="noData">
                <td colspan="3">
                    No data
                </td>
            </tr>
            </tbody>
        </table>
    </div>

    <script>
        $(function () {
            const $users = $(".users");
            const $noData = $users.find(".noData");
            $noData.find("td").text("Loading...");

            ajax({
                action: "findAll",
                success: function(response) {
                    response["users"].forEach(function(user) {
                        $noData.hide();
                        const $tpl = $($users.find("template").prop("content")).clone();
                        $tpl.find(".user_id").text(user["id"]);
                        $tpl.find(".user_login").text(user["login"]);
                        $tpl.find("tr").attr("data-userId", user["id"]);
                        $tpl.find("tr").attr("data-userAdmin", user["admin"]);
                        $users.find("tbody").append($tpl);
                    });

                    checkAdmin(function () {
                        $users.find("tr").each(function() {
                            const $tr = $(this);
                            const admin = $tr.boolAttr("data-userAdmin");
                            $tr.find("span").text(admin);
                            $tr.find(".button").val(admin ? "Disable" : "Enable");
                        });

                        $users.find(".button").click(function() {
                            const $button = $(this);
                            const $td = $button.parent();
                            const $tr = $td.parent();
                            const admin = !$tr.boolAttr("data-userAdmin");
                            $button.attr("disabled", true);

                            ajax({
                                action: "changePrivileges",
                                id: $tr.attr("data-userId"),
                                admin,
                                success: function (response) {
                                    if (response["error"]) {
                                        notify(response["error"], "error");
                                    } else {
                                        notify("You have changed privileges for this user");
                                        $button.val(admin ? "Disable" : "Enable");
                                        $td.find("span").text(admin);
                                        $tr.attr("data-userAdmin", admin);
                                    }
                                    $button.attr("disabled", false);
                                    checkAdmin(() => {});
                                }
                            });
                        });
                    });

                    /*$users.find("tr").click(function() {
                        ajax({
                            action: "findUser",
                            userId: $(this).attr("data-userId"),
                            success: function (response) {
                                notify(response["user"].creationTime);
                            }
                        })
                    });*/
                }
            });
        })
    </script>
</@c.page>
