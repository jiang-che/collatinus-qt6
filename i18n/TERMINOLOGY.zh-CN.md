# Collatinus 简体中文术语表（TERMINOLOGY.zh-CN.md）

本表用于统一 Collatinus 界面与文档中的中文译名，供人工审阅。
**界面语言（UI locale）与词条释义语言（`lemmes.*`）是两条独立的轴**；
本表只规范术语，不涉及具体词义数据。

维护规则：

- 同一概念在所有窗口、菜单、对话框、错误消息中必须使用同一译名；
- 拉丁语原文、专名、词典原文不强制翻译；
- 修改本表前请先确认没有其它窗口使用了不同译法；
- 形态学术语的数据层本地化（`morphos.zh` 等）属于 Phase 6，本表先固定译名。

## 1. 形态学核心术语

| 拉丁/英文 | 中文 | 说明 |
|---|---|---|
| lemma | 词元 | 词典收录形式；Collatinus 的核心输出 |
| inflection / flexion | 词形变化 | 动词变位与名词/形容词变格的统称 |
| morphology | 形态；形态分析 | |
| case | 格 | |
| number | 数 | |
| gender | 性 | |
| person | 人称 | |
| tense | 时态 | |
| **mood** | **式** | 由项目维护者指定，勿译为“语气/语式” |
| voice | 语态 | |
| conjugation | 变位 | 动词 |
| declension | 变格 | 名词/形容词 |
| degree | 级 | 形容词/副词 |
| participle | 分词 | |
| supine | 目的动名词 | |
| gerund | 动名词 | |
| gerundive | 动形词 | |
| scansion | 韵律划分 | 亦可用“音步划分”；界面统一用“韵律划分” |
| quantity | 音量 | 音节长短 |
| syllable | 音节 | |
| prosody | 韵律 | |

## 2. 格（case）

| 拉丁/英文 | 中文 |
|---|---|
| nominative | 主格 |
| genitive | 属格 |
| dative | 与格 |
| accusative | 宾格 |
| **ablative** | **夺格** |
| vocative | 呼格 |
| locative | 方位格 |

> 项目维护者指定：**ablative = 夺格**。

## 3. 式（mood）

| 拉丁/英文 | 中文 |
|---|---|
| indicative | 直陈式 |
| subjunctive | 虚拟式 |
| imperative | 命令式 |
| infinitive | 不定式 |
| participle | 分词 |
| supine | 目的动名词 |
| gerund | 动名词 |
| gerundive | 动形词 |

> 项目维护者指定：**mood = 式**。

## 4. 时态（tense）

| 拉丁/英文 | 中文 |
|---|---|
| present | 现在时 |
| imperfect | 未完成时 |
| future | 将来时 |
| perfect | 完成时 |
| pluperfect | 过去完成时 |
| future perfect | 将来完成时 |

## 5. 语态、性、数、人称、级

| 概念 | 中文 |
|---|---|
| active | 主动 |
| passive | 被动 |
| masculine | 阳性 |
| feminine | 阴性 |
| neuter | 中性 |
| singular | 单数 |
| plural | 复数 |
| first/second/third person | 第一/第二/第三人称 |
| positive | 原级 |
| comparative | 比较级 |
| superlative | 最高级 |

## 6. 界面与数据术语

| 法文/英文 | 中文 | 备注 |
|---|---|---|
| lemme / lemma | 词元 | |
| lemmatisation | 词形还原 | |
| dictionnaire / dictionary | 词典 | |
| lexique / lexicon | 词表 | Collatinus 的 `lemmes.*` 数据 |
| modules lexicaux | 词汇模块 | `.col` 包 |
| forme | 词形 | |
| radical | 词干 | |
| désinence | 词尾 | |
| variantes graphiques | 拼写变体 | |
| assimilation | 同化 | |
| contraction | 缩合 | |
| césure / hyphenation | 断词 | |

## 7. 待审阅项

下列译名尚未出现于 UI，或需维护者最终确认：

- `Calepino`（功能名）暂译“词汇速览”；
- `Tagger` 暂译“词性标注”；
- `scansion` 的“韵律划分/音步划分”二选一；
- `accusative` 采用“宾格”（部分教材作“受格”）。
