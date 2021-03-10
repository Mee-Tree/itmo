<#-- @ftlvariable name="comment" type="ru.itmo.wp.domain.Comment" -->
<#-- @ftlvariable name="viewedPost" type="ru.itmo.wp.domain.Post" -->
<#import "commons.ftlh" as c>

<@c.page>
    <#if viewedPost??>
        <@c.post post=viewedPost/>
        <div class="comments">
            <div class="title">
                <img src="<@c.spring.url '/img/comments_16x16.png'/>" alt="Comments" title="Comments">
                <span>Comments (${viewedPost.comments?size})</span>
            </div>

            <#if user??>
                <div class="comment">
                    <table class>
                        <tbody>
                        <tr>
                            <td class="left">You</td>
                            <td class="right">
                                <form method="post" action="">
                                    <textarea id="text" name="text"></textarea>
                                    <input type="submit" value="Publish">
                                    <@c.error "comment.text"/>
                                </form>
                            </td>
                        </tr>
                        </tbody>
                    </table>
                </div>
            </#if>

            <#list viewedPost.comments as comment>
                <@c.comment comment/>
            </#list>
        </div>
    <#else>
        <h3>No such post</h3>
    </#if>
</@c.page>
