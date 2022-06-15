# C++ 角度クラス

## 概要

角度を double で扱うと、単位を取り違える恐れがあります。
```cpp
sin( 45 ) ; // opps!
```

これを回避する為の、double値をラップしたクラスです。

## 使い方

* 定義は、単位を指定して行います。
```cpp
const auto angle_30 = math::Angle::Deg( 30 );     // 30°
const auto angle_45 = math::Angle::Rad( M_PI/4 ); // π/4 rad = 45°
```

* 値の取得も、単位を指定して行います。
```cpp
const auto angle_45 = math::Angle::Deg( 45 );

angle_45.Deg(); // 45
angle_45.Rad(); // π/4
```

* 四則演算,三角関数が使えます。
```cpp
const auto angle_30 = math::Angle::Deg( 30 );
const auto angle_15 = math::Angle::Deg( 15 );

angle_30 + angle_15; // 45°
2 * angle_15;        // 30°
sin( angle_30 );     // 0.5
```

* 大小比較は、単純に値の比較を行います。
```cpp
const auto a = math::Angle::Deg( -30 );
const auto b = math::Angle::Deg( +60 );
const auto c = math::Angle::Deg( 330 );

a < b;  // true
a == c; // false
```

* -30° ⇔ 330° の様な変換は、Normalize を使います。
```cpp
math::Angle::Deg( 365 ).Normalize<0,360>(); // 5°
math::Angle::Deg( -30 ).Normalize<0,360>(); // 330°

math::Angle::Deg( 365 ).Normalize<-180,180>(); // 5°
math::Angle::Deg( 330 ).Normalize<-180,180>(); // -30°

math::Angle::Deg( 190 ).Normalize<0,180>(); // 170°
math::Angle::Deg( -50 ).Normalize<0,180>(); // 50°

math::Angle::Deg( 120 ).Normalize<0,90>(); // 60°
math::Angle::Deg( 240 ).Normalize<0,90>(); // 60°

math::Angle::Deg( 120 ).Normalize<-90,90>(); // 60°
math::Angle::Deg( 300 ).Normalize<-90,90>(); // -60°
```

## note

* ポインタで扱う場合は、コピーコンストラクタを利用する。

```cpp
const auto angle_ptr = std::make_shared<math::Angle>( math::Angle::Deg( 10 ) );
```

<!-- * Utility的な部分を除いた、実装のコア部分 -->
* 定義に関する、実装のコア部分
```cpp
class Angle {
public:
	static constexpr Angle Rad( const double rad ) noexcept { return Angle{ rad } ; }
	static constexpr Angle Deg( const double deg ) noexcept { return Angle{ deg * rate_d_to_r } ; }

private:
	explicit constexpr Angle( const double rad ) noexcept : m_rad{ rad } {}

private:
	static constexpr double rate_d_to_r = M_PI / 180;

private:
	double m_rad{};
};
```

