$.fn.extend({
    isEmpty: function() {
        return !$(this).text().trim();
    },

    isImage: function() {
        return /^img$/i.test($(this)[0].tagName);
    },

    uniq: function() {
        return $.unique($(this))
            .filter(function () {
                return $(this).contents().length === 0;
            });
    },
    /*uniq: function() {
        let prev = null;
        return $.unique($(this))
            .filter(function () {
                const $this = $(this);
                const res = prev !== null ?
                    $this.text() !== prev.text() : true;
                prev = $this;
                return res;
            });
    },*/

    clearEmpty: function() {
        $($(this)
            .find('*')
            .get()
            .reverse())
            .each(function() {
                const $this = $(this);
                if ($this.isEmpty() && !$this.isImage()) {
                    $this.remove();
                }
            });
        return this;
    },

    cutTo: function(length) {
        let current = 0, $this = $(this);
        $this
            .find('*')
            .contents()
            .filter(function () {
                return !$(this).isEmpty();
            })
            .uniq()
            .each(function () {
                const $this = $(this);
                const content = $this.text();
                if (current + content.length >= length) {
                    current < length ?
                        $this.replaceWith(
                            content.substr(0, length - current) + "..."
                        ) : $this.remove();
                }
                current += content.length;
            });
        $this
            .clearEmpty();
    }
});
