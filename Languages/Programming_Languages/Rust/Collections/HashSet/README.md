**[HashSet](https://doc.rust-lang.org/std/collections/struct.HashSet.html) = unordered_set`<key>` C++**
- Create
  - [From vector](#vec)
- [Iterate](#itr)
- [Search a key](#search)

### Create
<a name=vec></a>
#### From vector
```rs
let vec: Vec<i32> = vec![1, 2, 3, 4];
let hash_set: HashSet<i32> = vec.into_iter().collect();          //Moving data ownership
let hash_set: HashSet<usize> = vec.iter().cloned().collect();    //Cloning the data
```

<a name=itr></a>
### Iterating thru elements
```rs
for j in &hash_set {              //j is borrowed means points to address of hashSet elements
  println("{}", *j);
}
```

<a name=search></a>
### Search a value
**pub fn `contains<Q: ?Sized>(&self, value: &Q) ->` bool**
- Returns true if the set contains a value.
```rs
  let mut j = 4;
  hash_set.contains(&j);
```
