(message "hello world")

(defun hello-world (name)
  "Say hell to user whose name is NAME."
  (message "Hello, %s" name))


(defvar g-foo "Did I have a vaule?"
  "A demo variable")


(defun circle-area (radix)
  (let ((pi 3.14)
        area)
    (setq area (* pi radix radix))
    (message "radix: %.2f, area: %.2f" radix area)))

(circle-area 3)

(let ((a 3) (b 4))
  (print (format "1a: %d" a))
  (print (format "1b: %d" b))
  (let ((a 5) (b 6))
    (print (format "2a: %d" a))
    (print (format "2b: %d" b))
    (setq a 10)
    (print (format "3a: %d" a)))
  (print (format "4a: %d" a)))

(setq test_lambda (lambda (name)
                    "documentation string"
                    (message "Hello, %s!" name)))

(funcall test_lambda "wdq")

(message "%d" most-positive-fixnum)


(progn
  (string-match "3\\(4\\)" "01234567890123456789")
  (match-data))

(let ((start 0))
  (while (string-match "34" "01234567890123456789" start)
    (princ (format "find at %d\n" (match-beginning 0)))
    (setq start (match-end 0))))


(let ((str "01234567890123456789"))
  (string-match "34" str)
  (princ (replace-match "x" nil nil str 0))
  (princ "\n")
  (princ str))

(cons 'a '(b))
(cons a b)
(cons 'a '(b c))


(setq foo '(+ 1 2 3 4 5 6))

(eval foo)


(setq a 123)
(eval 'a)


((lambda (arg) (erste arg))
 '(1 2 3))


(setq a 5)
(cond ((eq  a 'hack) 'foo)
      ((eq a 1) 'a))



(setq value ())

(dolist (elt '(a b c) value)
  (setq value (cons elt value)))


(defun foo-outer ()
  (catch 'foo (foo-inner)))

(defun foo-inner ()
  (throw 'foo t))


(foo-outer)


(defun search-foo ()
  (catch 'loop
    (let ((i 0))
      (while (< i 10)
        (let ((j 0))
          (while (< j 10)
            (if (foo i j)
                (throw 'loop (list i j)))
            (setq j (1+ j))))
        (setq i (1+ i))))))
