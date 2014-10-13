<?php

/**
 * Custom function from php.net
 *
 * @param callable $func
 * @param array $arr
 * @return array
 */
function array_map_recursive($func, array $arr) {
  /*
  // This is the PHP Version >= 5.5
  // $func must be a callable.
  array_walk_recursive($arr, function(&$v) use ($func) {
    $v = $func($v);
  });
  return $arr;
  */
  foreach ($arr as $key => $value) {
    if (is_array($arr[$key])) {
      $arr[$key] = array_map_recursive($func, $arr[$key]);
    }
    else {
      $arr[$key] = call_user_func($func, $arr[$key]);
    }
  }
  return $arr;
}

function _floatval_if_numeric($var) {
  if (is_numeric($var)) {
    return floatval($var);
  }
  return $var;
}

function removeEmptyElements($array) {
  foreach($array as $key => $value) {
    if (empty($value) && $value != 0) {
      unset($array[$key]);
    } else if (is_array($value)) {
      $array[$key] = removeEmptyElements($value);
    }
  }
  return $array;
}
