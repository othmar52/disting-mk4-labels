
<?php
/**
 * This file converts a CSV to a C++ file
 * for an arduino sketch.
 */

$filepath = dirname(__FILE__) . DIRECTORY_SEPARATOR . 'disting-mk4-algorithms-v4.20.csv';

function fillChunk($array, $parts) {
    $t = 0;
    $result = array_fill(0, $parts - 1, array());
    $max = ceil(count($array) / $parts);
    foreach($array as $v) {
        count($result[$t]) >= $max and $t ++;
        $result[$t][] = $v;
    }
    return $result;
}

function getCommentForTripleGroup($idx) {
    $word = "";
    switch($idx) {
        case 0: $word = "patch"; break;
        case 1: $word = "title"; break;
        case 2: $word = "  Z  "; break;
        case 3: $word = "  X  "; break;
        case 4: $word = "  Y  "; break;
        case 5: $word = "  A  "; break;
        case 6: $word = "  B  "; break;
    }
    return "    /* {$word} */ ";
}
$headerSkipped = false;
$patchLines = "";
if (($handle = fopen($filepath, "r")) !== FALSE) {
    while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {
        if($headerSkipped === false) {
            $headerSkipped = true;
            continue;
        }
        $tripleGroups = fillChunk($data, 7);
        foreach($tripleGroups as $idx => $tripleGroup) {
            $patchLines .= getCommentForTripleGroup($idx);
            $patchLines .= "\"" . join('", "', $tripleGroup) . "\",\n";
        }
        $patchLines .= "\n";
    }
    fclose($handle);
}

$patchLines = rtrim($patchLines, "\n,") . "\n";

$template = <<<EOF
// see http://distingquickguide.rustle.works/
// see http://www.vo1t.com/Euro/Illustrated/ESdistingMk4V4.9.pdf
// see https://www.expert-sleepers.co.uk/downloads/manuals/disting_user_manual_4.20.pdf

const int wordsPerPatch = 21;
const char *allWords[] = {
$patchLines
};

int numPatches = 0;
int getTotalEntries() {
  while(allWords[numPatches])
  {
     numPatches++;
  }
  numPatches = numPatches/wordsPerPatch;
  return numPatches;
}

EOF;


echo $template; exit;
