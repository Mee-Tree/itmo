window.notify = function (message, className = "success") {
    $.notify(message, {
        position: "right bottom",
        className
    });
};

window.ajax = function (config) {
    const {success, ...data} = config;
    $.ajax({
        type: "POST",
        url: "",
        dataType: "json",
        data,
        success: function (response) {
            if (config.hasOwnProperty("success")) {
                config["success"](response);
            }
            if (response["redirect"]) {
                location.href = response["redirect"];
            }
        }
    });
}

window.checkAdmin = function (success) {
    ajax({
        action: "checkAdmin",
        success: function(response) {
            const $admin = $("[class*='admin']");

            if (!response["admin"]) {
                $admin.hide();
                return;
            }
            $admin.show();
            success();
        }
    });
}

$.fn.extend({
    boolAttr: function(name) {
        const attr = $(this).attr(name);
        return attr === "true" ? true
            : attr === "false" ? false
            : undefined;
    },
});
