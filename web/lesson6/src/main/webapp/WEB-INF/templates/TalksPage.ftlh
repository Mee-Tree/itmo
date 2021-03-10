<#-- @ftlvariable name="recipient" type="ru.itmo.wp.model.domain.User" -->
<#-- @ftlvariable name="user" type="ru.itmo.wp.model.domain.User" -->
<#-- @ftlvariable name="talks" type="ru.itmo.wp.model.domain.Talk[]" -->
<#-- @ftlvariable name="messages" type="java.lang.String[]" -->
<#-- @ftlvariable name="users" type="ru.itmo.wp.model.domain.User[]" -->
<#import "commons.ftlh" as c>

<@c.page>
    <div class="form-box">
        <div class="body">
            <form method="post" action="">
                <input type="hidden" name="action" value="sendMessage"/>
                <div class="field">
                    <div class="name">
                        <label for="user-list">Select user:</label>
                    </div>
                    <div class="value">
                        <select id="user-list" name="targetUserId">
                            <#list users as user>
                                <option value="${user.id}">${user.login}</option>
                            </#list>
                        </select>
                    </div>
                </div>
                <div class="field">
                    <div class="name">
                        <label for="messages-form__text">Enter your message:</label>
                    </div>
                    <div class="value">
                        <textarea name="text" id="messages-form__text"
                                  maxlength="1000" rows="6" cols="25"></textarea>
                    </div>
                </div>
                <div class="button-field">
                    <input type="submit" value="Send">
                </div>
            </form>
        </div>

        <div class="datatable">
            <table>
                <tbody>
                <tr>
                    <th>Author</th>
                    <th>Recipient</th>
                    <th>Message</th>
                </tr>

                <#list talks as talk>
                    <tr>
                        <#assign targetHandle = c.findBy(users, "id", talk.targetUserId).login>
                        <#if user.id == talk.sourceUserId>
                            <td><a href="#">You</a></td>
                            <td><a href="#">${targetHandle}</a></td>
                        <#else>
                            <td><a href="#">${targetHandle}</a></td>
                            <td><a href="#">You</a></td>
                        </#if>
                        <td>${talk.text}</td>
                    </tr>
                </#list>
                </tbody>
            </table>
        </div>
    </div>

</@c.page>
