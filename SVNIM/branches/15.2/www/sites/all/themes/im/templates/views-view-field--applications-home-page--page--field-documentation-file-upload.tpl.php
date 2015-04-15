<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */

global $is_https;
$url = '';
$final_url = $url;
$result = explode('"',$output);
if(isset($result[1])) {
  $url = trim($result[1]);
  $url = str_replace('////', '//', $url);
  $url = str_replace('///', '//', $url);
  if ($is_https) {
   if (!strstr($url, "https:")) {
    $url = "https:" . $url;
   }
  }
  else {
   if (!strstr($url, "http:")) {
    $url = "http:" . $url;
   }
  }
  $result[1] = $url;
}
$output = implode('"', $result);
print urldecode($output);