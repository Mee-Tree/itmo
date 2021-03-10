<#-- @ftlvariable name="user_id" type="java.lang.Long" -->
<#import "./common.ftlh" as c>

<@c.page>
    <#if user_id??>
        <#assign userPosts = c.userPosts(user_id)>
        <#if userPosts?size gt 0>
            <#list userPosts as post>
                <@c.postView post/>
            </#list>
        <#else>
            No posts
        </#if>
    </#if>
    <script>
        $('article .body').each(function() {
            $(this).cutTo(250);
        });
    </script>
</@c.page>
