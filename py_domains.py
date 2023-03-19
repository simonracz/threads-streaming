import requests

urls = ["https://www.google.com", "https://www.example.com", "https://www.kpn.com"]
statuses = []

for url in urls:
    response = requests.get(url)
    status = response.status_code
    statuses.append(status)

print("Statuses:")
print(statuses)
