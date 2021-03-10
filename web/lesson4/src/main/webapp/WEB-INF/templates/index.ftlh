<#import "./common.ftlh" as c>

<@c.page>
    <#list posts?reverse as post>
        <@c.postView post/>
    </#list>
    <script>
        $('article .body').each(function() {
            $(this).cutTo(180);
        });
    </script>
</@c.page>
