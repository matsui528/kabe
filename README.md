# 壁集合

集合を表現するデータ構造の比較です。[壁アドベントカレンダー2025の記事](https://mti-lab.github.io/blog/2025/12/20/kabe_set.html)の検証リポジトリです。

- `std::set`
- `std::unordered_set`
- `boost::container::flat_set`
- `boost::unordered_flat_set`
- `boost::bloom::filter`

BloomのためにBoost 1.89+が必要なのでソースをダウンロードしています。ヘッダオンリーでいけるので、ソースダウンロード後に単純にインクルードパスを指定しています。

7524個の要素をデータ構造に挿入します。それに対し、
- 既に含まれている1000個の要素の検索
- 含まれていない1000個の要素の検索
を行い、時間を計測します。


## 結果
```
=== std::set ===
Set size: 7524
Existing terms (1000 found): 197 μs
Non-existing terms (0 found): 181 μs

=== std::unordered_set ===
Set size: 7524
Existing terms (1000 found): 59 μs
Non-existing terms (0 found): 50 μs

=== boost::container::flat_set ===
Set size: 7524
Existing terms (1000 found): 196 μs
Non-existing terms (0 found): 199 μs

=== boost::unordered_flat_set ===
Set size: 7524
Existing terms (1000 found): 23 μs
Non-existing terms (0 found): 13 μs

=== boost::bloom::filter ===
Existing terms (1000 found): 12 μs
Non-existing terms (119 found): 17 μs
```