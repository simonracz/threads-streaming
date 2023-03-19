use std::error::Error;
use reqwest::StatusCode;
use futures::future::join_all;

#[tokio::main]
async fn main() -> Result<(), Box<dyn Error>> {
    let urls = vec![
        "https://www.example.com",
        "https://www.google.com",
        "https://www.kpn.com",
    ];
    let mut futures = Vec::new();
    for url in urls {
        futures.push(async move {
            let resp = reqwest::get(url).await?;
            Ok::<StatusCode, reqwest::Error>(resp.status())
        });
    }
    let statuses = join_all(futures).await;
    println!("{:?}", statuses);
    Ok(())
}

/*
use std::error::Error;

#[tokio::main]
async fn main() -> Result<(), Box<dyn Error>> {
    let urls = vec![
        "https://www.example.com",
        "https://www.google.com",
        "https://www.kpn.com",
    ];
    let mut statuses = Vec::new();
    for url in urls {
        let resp = reqwest::get(url).await?;
        statuses.push(resp.status());
    }
    println!("{:?}", statuses);
    Ok(())
}
*/
