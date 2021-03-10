<#-- @ftlvariable name="user_id" type="java.lang.Long" -->
<#-- @ftlvariable name="handle" type="java.lang.String" -->
<#import "./common.ftlh" as c>

<@c.page>
    <#if handle??>
        <#assign u = c.findBy(users, "handle", handle)!/>
    <#elseif user_id??>
        <#assign u = c.findBy(users, "id", user_id)!/>
    </#if>

    <#if u?has_content>
        <div class="user-box">
            <img alt="No title" src="../../img/no-title.jpg"/>
            <div class="name">
                <@c.userlink u false>${u.name}</@c.userlink>
            </div>
            <div class="info">
                <ul>
                    <li>id: ${u.id}</li>
                    <li>handle: ${u.handle}</li>
                    <li>name: ${u.name}</li>
                </ul>
                <a href="/posts?user_id=${u.id}">Blog Entries (${c.userPosts(u.id)?size})</a>
            </div>
        </div>
        <nav>
            <#assign user_index = users?seq_index_of(u)/>
            <ul>
                <li><@arrowlink user_index - 1>←</@arrowlink></li>
                <li><@arrowlink user_index + 1>→</@arrowlink></li>
            </ul>
        </nav>
    <#else>
        No such user
    </#if>
</@c.page>

<#macro arrowlink user_index>
    <#if user_index lt users?size && user_index gte 0>
        <a href="/user?handle=${users[user_index].handle}"
           style="text-decoration: none"><#nested></a>
    <#else>
        <#nested>
    </#if>
</#macro>