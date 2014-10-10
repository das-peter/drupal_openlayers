<?php

/**
 * Custom function from php.net
 *
 * @param callable $func
 * @param array $arr
 * @return array
 */
function array_map_recursive(callable $func, array $arr) {
  array_walk_recursive($arr, function(&$v) use ($func) {
    $v = $func($v);
  });
  return $arr;
}

function _floatval_if_numeric($var) {
  if (is_numeric($var)) {
    return floatval($var);
  }
  return $var;
}
