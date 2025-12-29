(require memo)

(define (read-input lines acc)
  (if (null? lines) acc
      (read-input (cdr lines)
                  (hash-set acc
                            (substring (car lines) 0 3)
                            (drop (string-split (car lines) " ") 1)))))

(define/memoize (count-paths start dac fft)
  (if (and (string=? start "out") dac fft) 1
      (foldl + 0
             (map (λ (x) (count-paths x (or dac (string=? start "dac"))
                                      (or fft (string=? start "fft"))))
                  (hash-ref input start null)))))

(define input (read-input (file->lines "input.txt") (hash)))

(display "Part 1: ")
(count-paths "you" true true)
(display "Part 2: ")
(count-paths "svr" false false)