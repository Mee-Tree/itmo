<#-- @ftlvariable name="uri" type="java.lang.String" -->
<#macro page>
    <!DOCTYPE html>
    <html lang="ru">
    <head>
        <meta charset="UTF-8">
        <title>Codeforces</title>
        <link rel="stylesheet" href="/css/normalize.css">
        <link rel="stylesheet" href="/css/style.css">
        <link rel="icon" href="/favicon.ico">
        <script src="/js/jquery-1.8.3.js"></script>
        <script src="/js/post-cut.js"></script>
    </head>
    <body>
    <@header/>
    <div class="middle">
        <@sidebar/>
        <main>
            <#nested/>
        </main>
    </div>
    <@footer/>
    </body>
    </html>
</#macro>

<#macro header>
    <header>
        <a href="#" class="logo"><img alt="Codeforces" title="Codeforces"
                                      src="/img/codeforces-vs-coronavirus-65.png"></a>
        <div class="languages">
            <a href="#"><img alt="In English" title="In English"
                             src="/img/gb.png"></a>
            <a href="#"><img alt="In Russian" title="In Russian"
                             src="/img/ru.png"></a>
        </div>
        <div class="enter-or-register-box">
            <#if user??>
                <@userlink user true>${user.name}</@userlink>
                |
                <a href="/logout">Logout</a>
            <#else>
                <a href="/enter">Enter</a>
                |
                <a href="/register">Register</a>
            </#if>
        </div>
        <nav>
            <#assign items=[
            {"href": "/index", "name": "Home"},
            {"href": "/misc/help", "name": "Help"},
            {"href": "/contests", "name": "Contests"},
            {"href": "/users", "name": "Users"}
            ]/>
            <ul>
                <#list items as item>
                    <#assign style="${(uri?? && item.href?starts_with(uri))?then(
                        'border-bottom: 3px solid var(--caption-color);', '')}"/>
                    <li><a href="${item.href}" style="${style}">${item.name}</a></li>
                </#list>
            </ul>
        </nav>
    </header>
</#macro>

<#macro sidebar>
    <aside>
        <#list posts?reverse as post>
            <section>
                <div class="header">Post #${post.id}</div>
                <div class="body">
                    <@postBody post/>
                </div>
                <div class="footer">
                    <a href="/post?post_id=${post.id}">View all</a>
                </div>
            </section>
        </#list>
        <script>
            $('section .body').each(function() {
                $(this).cutTo(250);
            });
        </script>
    </aside>
</#macro>

<#macro postView p>
    <article>
        <div class="title">
            ${p.title}
        </div>
        <div class="information">
            <#assign user = findBy(users, "id", p.userId)>
            By <@userlink user false>${user.handle}</@userlink>, 2 days ago
        </div>
        <div class="body">
            <@postBody p/>
        </div>
        <div class="footer">
            <div class="left">
                <img src="img/voteup.png" title="Vote Up" alt="Vote Up"/>
                <span class="positive-score">+173</span>
                <img src="img/votedown.png" title="Vote Down" alt="Vote Down"/>
            </div>
            <div class="right">
                <img src="img/date_16x16.png" title="Publish Time" alt="Publish Time"/>
                2 days ago
                <img src="img/comments_16x16.png" title="Comments" alt="Comments"/>
                <a href="#">68</a>
            </div>
        </div>
    </article>
</#macro>

<#macro postBody p>
    ${p.text?no_esc}
</#macro>

<#macro footer>
    <footer>
        2010-2020 &copy; by Mike Mirzayanov
    </footer>
</#macro>

<#macro userlink user nameOnly>
    <#assign class = "">
    <#if !nameOnly>
        <#assign class = "rated-user user-${user.color}">
    </#if>
    <a href="/user?handle=${user.handle}" class="${class}"><#nested/></a>
</#macro>

<#function userPosts id>
    <#return posts?reverse?filter(x -> x.userId == id) />
</#function>

<#function findBy items key value>
    <#list items as item>
        <#if item[key] == value>
            <#return item/>
        </#if>
    </#list>
</#function>
