<#-- @ftlvariable name="users" type="ru.itmo.wp.domain.User[]" -->
<#import "commons.ftlh" as c>

<@c.page>
    <#if user??>
        <div class="users datatable">
            <div class="caption">User</div>
            <table>
                <thead>
                <tr>
                    <th>Id</th>
                    <th>Login</th>
                    <th>Created</th>
                    <th>Enable/Disable</th>
                </tr>
                </thead>
                <tbody>
                <#if users?size==0>
                    <tr class="noData">
                        <td colspan="4">
                            No data
                        </td>
                    </tr>
                <#else>
                    <#list users as u>
                        <tr>
                            <td class="id">${u.id}</td>
                            <td class="login">${u.login}</td>
                            <td class="creationTime">${u.creationTime}</td>
                            <td class="disabled">
                                <form method="post" action="">
                                    <input type="hidden" name="id" value="${u.id}">
                                    <input class="button" name="state" type="submit"
                                           value="${u.disabled?then("Enable", "Disable")}"
                                            ${(u.id == user.id)?then("disabled", "")}/>
                                </form>

                            </td>
                        </tr>
                    </#list>
                </#if>
                </tbody>
            </table>
        </div>
    <#else>
        <h3>Access denied</h3>
    </#if>
</@c.page>
