<#-- @ftlvariable name="user_id" type="java.lang.Long" -->
<#-- @ftlvariable name="handle" type="java.lang.String" -->
<#import "commons.ftlh" as c>

<@c.page>
    <#assign u = viewedUser!/>
    <#if u?has_content>
        <div class="user-box">
            <img alt="No title" src="<@c.spring.url '/img/no-title.jpg'/>"/>
            <div class="name">
                <@c.userlink u/>
            </div>
            <div class="info">
                <ul>
                    <li>id: ${u.id}</li>
                    <li>login: ${u.login}</li>
                    <li>creation: ${u.creationTime}</li>
                </ul>
            </div>
        </div>
    <#else>
        <h3>No such user</h3>
    </#if>
</@c.page>