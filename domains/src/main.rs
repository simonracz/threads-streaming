use std::error::Error;
// use std::{thread, time};

fn main() -> Result<(), Box<dyn Error>> {
    let urls = vec![
        "https://www.example.com",
        "https://www.google.com",
        "https://www.kpn.com",
    ];
    let mut statuses = Vec::new();
    for url in urls {
        let resp = reqwest::blocking::get(url)?;
        statuses.push(resp.status());
        // let seconds = time::Duration::from_secs(5);
        // thread::sleep(seconds);
    }
    println!("{:?}", statuses);
    Ok(())
}

