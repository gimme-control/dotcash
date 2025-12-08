%builtins output range_check pedersen

from starkware.cairo.common.cairo_builtins import HashBuiltin
from starkware.cairo.common.hash import hash2

struct TransferWitness {
    val_in: felt,
    val_out: felt,
    fee: felt,
    salt_in: felt,
    salt_out: felt,
}

func main{output_ptr: felt*, range_check_ptr, pedersen_ptr: HashBuiltin*}() {
    alloc_locals;
    
    local val_in;
    local val_out;
    local fee;
    local salt_in;
    local salt_out;
    
    assert val_in = val_out + fee;
    
    let (cm_in) = hash2{hash_ptr=pedersen_ptr}(val_in, salt_in);
    let (cm_out) = hash2{hash_ptr=pedersen_ptr}(val_out, salt_out);
    
    assert [output_ptr] = cm_in;
    assert [output_ptr + 1] = cm_out;
    
    let output_ptr = output_ptr + 2;
    return ();
}

