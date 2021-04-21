;;; -*- lexical-binding: t; -*-
(defun some-other-function ()
  (message "I see `c', its value is: %s" c))

(defvar c t)

(let ((a "I'm lexically bound")
      (c "I'm special and therefore dynamically bound"))
  (some-other-function)
  (message "I see `a', its values is: %s" a))



(defmacro my-set-buffer-multibyte (arg)
  (if (fboundp ’set-buffer-multibyte)
      (set-buffer-multibyte arg)))

(my-set-buffer-multibyte 'a)
