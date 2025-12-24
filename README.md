# 壁集合

集合を表現するデータ構造の比較です。[壁アドベントカレンダー2025の記事](https://mti-lab.github.io/blog/2025/12/20/kabe_set.html)の検証リポジトリです。

- `std::set`
- `std::unordered_set`
- `boost::container::flat_set`
- `boost::unordered_flat_set`
- `boost::bloom::filter`

BloomのためにBoost 1.89+が必要なのでソースをダウンロードしています。ヘッダオンリーでいけるので、ソースダウンロード後に単純にインクルードパスを指定しています。