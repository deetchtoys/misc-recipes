(defmacro my-set-buffer-multibyte (arg)
  (if (fboundp ’set-buffer-multibyte)
      ‘(set-buffer-multibyte ,arg)))


(defmacro my-print-2 (number)
  (message "This is a number: %d" number))

(my-print-2 (+ 2 3))


(defun foo (a)
  (list 'setq (eval a) t))

(setq x 'b)

(foo x)

(setq wdq '(1 2 (+ 1 2)))
