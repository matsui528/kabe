# 壁集合

集合を表現するデータ構造の比較です。[壁アドベントカレンダー2025の記事](https://mti-lab.github.io/blog/2025/12/20/kabe_set.html)の検証リポジトリです。

- `std::set`
- `std::unordered_set`
- `boost::container::flat_set`
- `boost::unordered_flat_set`
- `boost::bloom::filter`

BloomのためにBoost 1.89+が必要なのでソースをダウンロードしています。ヘッダオンリーでいけるので、ソースダウンロード後に単純にインクルードパスを指定しています。

Actionsで自動的に実行してベンチをとります。


## ベンチマーク方法
7524個の要素をデータ構造に挿入します。それに対し、
- 既に含まれている1000個の要素の検索
- 含まれていない1000個の要素の検索
を行い、時間を計測します。


## 結果
```
=== std::set ===
Set size: 7524
Existing terms (1000 found): 226 μs
Non-existing terms (0 found): 192 μs
=== std::unordered_set ===
Set size: 7524
Existing terms (1000 found): 74 μs
Non-existing terms (0 found): 65 μs
=== boost::container::flat_set ===
Set size: 7524
Existing terms (1000 found): 206 μs
Non-existing terms (0 found): 200 μs
=== boost::unordered_flat_set ===
Set size: 7524
Existing terms (1000 found): 32 μs
Non-existing terms (0 found): 14 μs
=== boost::bloom::filter ===
Existing terms (1000 found): 11 μs
Non-existing terms (200 found): 18 μs
```

- bloomが最速ですが、擬陽性が119個発生しています（義陽性率9%程度で設定していたので、大体想定通りです）。
- その次に速いのはunordered_flat_setで、これが一番良さそうです。
- unordered_setはその倍程度かかりますが十分早いです。boostを使えない場合はこれがいいです。
- setはその3倍くらい時間がかかったようです。flat_setは、今回のケースではsetと同程度でした。