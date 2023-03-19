package main

import (
	"fmt"
	"net/http"
	"sync"
)

func main() {
	domains := []string{"google.com", "example.com", "www.kpn.com"}
	statuses := make([]int, len(domains))
	wg := sync.WaitGroup{}

	for i, domain := range domains {
		wg.Add(1)
		go func(i int, domain string) {
			defer wg.Done()

			resp, err := http.Get("https://" + domain)
			if err != nil {
				statuses[i] = -1
				return
			}
			statuses[i] = resp.StatusCode
			resp.Body.Close()
		}(i, domain)
	}

	wg.Wait()

	for i, domain := range domains {
		status := statuses[i]
		if status == -1 {
			fmt.Printf("%s: error\n", domain)
		} else {
			fmt.Printf("%s: %d\n", domain, status)
		}
	}
}
