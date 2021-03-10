<#-- @ftlvariable name="post_id" type="java.lang.Long" -->
<#-- @ftlvariable name="id" type="java.lang.Long" -->
<#-- @ftlvariable name="text" type="java.lang.String" -->
<#import "./common.ftlh" as c>

<@c.page>
    <#if post_id??>
        <#assign p = c.findBy(posts, "id", post_id)!/>
    </#if>

    <#if p?has_content>
        <@c.postView p/>
    <#else>
        No such post
    </#if>
</@c.page>
