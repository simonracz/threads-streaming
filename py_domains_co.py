import asyncio
import aiohttp

async def fetch_status(session, url):
    async with session.get(url) as response:
        return response.status

async def main():
    domains = ['https://www.example.com', 'https://www.google.com', 'https://www.kpn.com']
    statuses = []

    async with aiohttp.ClientSession() as session:
        tasks = [fetch_status(session, domain) for domain in domains]
        statuses = await asyncio.gather(*tasks)

    print(statuses)

if __name__ == '__main__':
    asyncio.run(main())

