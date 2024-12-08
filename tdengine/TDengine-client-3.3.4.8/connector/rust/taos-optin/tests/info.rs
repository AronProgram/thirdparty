#[test]
fn test_server_info() {
    use taos_optin::TaosBuilder;
    use taos_query::prelude::sync::*;

    let version = TaosBuilder::client_version();
    dbg!(version);

    let builder = TaosBuilder::from_dsn("taos://").unwrap();

    let client = builder.build().unwrap();
    let version: String = client
        .query_one("select server_version()")
        .unwrap()
        .unwrap();

    dbg!(version);
}
