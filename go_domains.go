package main

import (
	"fmt"
	"net/http"
)

func main() {
	domains := []string{"www.google.com", "www.example.com", "www.kpn.com"}
	statuses := make([]int, len(domains))

	for i, domain := range domains {
		resp, err := http.Get("https://" + domain)
		if err != nil {
			statuses[i] = -1
			continue
		}
		statuses[i] = resp.StatusCode
		resp.Body.Close()
	}

	for i, domain := range domains {
		status := statuses[i]
		if status == -1 {
			fmt.Printf("%s: error\n", domain)
		} else {
			fmt.Printf("%s: %d\n", domain, status)
		}
	}
}

